/*
 * Copyright (C) 2022 Tommi Maekitalo
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "sslctximpl.h"
#include <cxxtools/systemerror.h>
#include <cxxtools/fileinfo.h>
#include <cxxtools/mutex.h>
#include <cxxtools/log.h>

#include <openssl/ssl.h>

#include <cstring>
#include <stdlib.h>

#include "config.h"

log_define("cxxtools.sslctx.impl")

namespace cxxtools
{

static Mutex *openssl_mutex = nullptr;
static Mutex sslMutex;
static bool sslInitialized = false;

static unsigned long pthreads_thread_id()
    { return (unsigned long)pthread_self(); }

static void pthreads_locking_callback(int mode, int n, const char* /* file */, int /* line */)
{
    if (mode & CRYPTO_LOCK)
        openssl_mutex[n].lock();
    else
        openssl_mutex[n].unlock();
}

static void thread_setup()
{
    openssl_mutex = new Mutex[CRYPTO_num_locks()];

    CRYPTO_set_id_callback(pthreads_thread_id);
    CRYPTO_set_locking_callback(pthreads_locking_callback);
}

SslCtx::Impl::Impl()
{
    MutexLock lock(sslMutex);
    if (!sslInitialized)
    {
        log_debug("SSL_library_init");
        SSL_library_init();

        SslError::checkSslError();

        thread_setup();

        sslInitialized = true;
    }

#ifdef HAVE_TLS_METHOD
    log_debug("SSL_CTX_new(TLS_method())");
    _ctx = SSL_CTX_new(TLS_method());
#else
    log_debug("SSL_CTX_new(SSLv23_method())");
    _ctx = SSL_CTX_new(SSLv23_method());
#endif

    log_debug("ctx=" << static_cast<void*>(ctx()));
    SslError::checkSslError();
}

SslCtx::Impl::~Impl()
{
    log_debug("SSL_CTX_free(" << static_cast<void*>(_ctx) << ')');
    SSL_CTX_free(_ctx);
}


void SslCtx::Impl::loadCertificateFile(const std::string& certFile, const std::string& privateKeyFile)
{
    log_debug("load ssl certificate file \"" << certFile << '"');
    int ret = SSL_CTX_use_certificate_chain_file(ctx(), certFile.c_str());
    if (ret != 1)
        SslError::checkSslError();

    std::string key = privateKeyFile.empty() ? certFile : privateKeyFile;
    log_debug("load ssl private key file \"" << key << '"');
    ret = SSL_CTX_use_PrivateKey_file(ctx(), key.c_str(), SSL_FILETYPE_PEM);
    if (ret != 1)
        SslError::checkSslError();

    log_debug("check private key");
    if (!SSL_CTX_check_private_key(ctx()))
        throw SslError("private key does not match the certificate public key", 0);

    log_debug("private key ok");
}

void SslCtx::Impl::setVerify(int level, const std::string& ca)
{
    if (level > 0)
    {
        cxxtools::FileInfo fileInfo(ca);
        STACK_OF(X509_NAME)* names = SSL_load_client_CA_file(ca.c_str());
        log_debug("SSL_load_client_CA_file => " << names << " (" << sk_X509_NAME_num(names) << ')');

        log_debug("SSL_CTX_set_client_CA_list");
        SSL_CTX_set_client_CA_list(ctx(), names);

        log_debug_if(fileInfo.isFile(), "load verify locations file \"" << ca << '"');
        log_debug_if(fileInfo.isDirectory(), "load verify locations directory \"" << ca << '"');
        int ret = SSL_CTX_load_verify_locations(ctx(),
            fileInfo.isFile()      ? ca.c_str() : 0,
            fileInfo.isDirectory() ? ca.c_str() : 0);

        if (ret == 0)
            SslError::checkSslError();
    }

    log_debug("set ssl verify level " << level);
    SSL_CTX_set_verify(
        ctx(),
        level == 0 ? SSL_VERIFY_NONE :
        level == 1 ? (SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE) :
                     (SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT | SSL_VERIFY_CLIENT_ONCE),
        0);

    char hostname[HOST_NAME_MAX];
    ::gethostname(hostname, sizeof(hostname));
    log_debug("SSL_CTX_set_session_id_context(" << static_cast<void*>(ctx()) << ", " << hostname << ')');
    int ret = SSL_CTX_set_session_id_context(ctx(), reinterpret_cast<const unsigned char*>(hostname), std::max(static_cast<size_t>(SSL_MAX_SSL_SESSION_ID_LENGTH), std::strlen(hostname)));
    if (ret == 0)
        SslError::checkSslError();
}

#ifdef SSL_CTX_set_min_proto_version
static long openSslProtocolVersion(SslCtx::PROTOCOL_VERSION v)
{
    switch (v)
    {
        case SslCtx::PROTOCOL_VERSION::SSLv2: return SSL2_VERSION;
        case SslCtx::PROTOCOL_VERSION::SSLv3: return SSL3_VERSION;
        case SslCtx::PROTOCOL_VERSION::TLSv1: return TLS1_VERSION;
        case SslCtx::PROTOCOL_VERSION::TLSv11: return TLS1_1_VERSION;
        case SslCtx::PROTOCOL_VERSION::TLSv12: return TLS1_2_VERSION;
        case SslCtx::PROTOCOL_VERSION::TLSv13: return TLS1_3_VERSION;
    }

    return 0;
}
#endif

void SslCtx::Impl::setProtocolVersion(PROTOCOL_VERSION min_version, PROTOCOL_VERSION max_version)
{
    log_debug("setProtocolVersion(" << static_cast<unsigned short>(min_version) << ", " << static_cast<unsigned short>(max_version) << ')');

#ifdef SSL_CTX_set_min_proto_version
    if (min_version > PROTOCOL_VERSION::SSLv2)
    {
        log_debug("SSL_CTX_set_min_proto_version(" << static_cast<void*>(_ctx) << ", " << static_cast<int>(min_version) << '/' << openSslProtocolVersion(min_version) << ')');
        if (SSL_CTX_set_min_proto_version(_ctx, openSslProtocolVersion(min_version)) == 0)
            throw cxxtools::SslError("failed to set minimum protocol version", 0);
    }

    if (max_version < PROTOCOL_VERSION::TLSv13)
    {
        log_debug("SSL_CTX_set_max_proto_version(" << static_cast<void*>(_ctx) << ", " << static_cast<int>(max_version) << '/' << openSslProtocolVersion(max_version) << ')');
        if (SSL_CTX_set_max_proto_version(_ctx, openSslProtocolVersion(max_version)) == 0)
            throw cxxtools::SslError("failed to set maximum protocol version", 0);
    }

#else
    long options = 0;

    if (min_version > PROTOCOL_VERSION::SSLv2)
    {
        log_debug("deactivate SSLv2 " << std::hex << SSL_OP_NO_SSLv2);
        options |= SSL_OP_NO_SSLv2;
    }
    if (min_version > PROTOCOL_VERSION::SSLv3 || max_version < PROTOCOL_VERSION::SSLv3)
    {
        log_debug("deactivate SSLv3 " << std::hex << SSL_OP_NO_SSLv3);
        options |= SSL_OP_NO_SSLv3;
    }
    if (min_version > PROTOCOL_VERSION::TLSv1 || max_version < PROTOCOL_VERSION::TLSv1)
    {
        log_debug("deactivate TLSv1 " << std::hex << SSL_OP_NO_TLSv1);
        options |= SSL_OP_NO_TLSv1;
    }
    if (min_version > PROTOCOL_VERSION::TLSv11 || max_version < PROTOCOL_VERSION::TLSv11)
    {
        log_debug("deactivate TLSv1_1 " << std::hex << SSL_OP_NO_TLSv1_1);
        options |= SSL_OP_NO_TLSv1_1;
    }
    if (min_version > PROTOCOL_VERSION::TLSv12 || max_version < PROTOCOL_VERSION::TLSv12)
    {
        log_debug("deactivate TLSv1_2 " << std::hex << SSL_OP_NO_TLSv1_2);
        options |= SSL_OP_NO_TLSv1_2;
    }

    if (options != 0)
    {
        log_debug("SSL_CTX_set_options(ctx, " << options << ')');
        long newOptions = SSL_CTX_set_options(_ctx, options);
        log_debug("new options=" << std::hex << newOptions);
    }
#endif
}

void SslCtx::Impl::setCiphers(const std::string& ciphers)
{
    log_debug("SSL_CTX_set_cipher_list(\"" << ciphers << "\")");
    if (SSL_CTX_set_cipher_list(_ctx, ciphers.c_str()) == 0)
        SslError::checkSslError();
}

}
