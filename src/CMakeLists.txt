project( cxxtools VERSION 3.1 LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSION ON )

set( cxxtools_sources addrinfo.cpp
                      addrinfoimpl.cpp
                      application.cpp
                      applicationimpl.cpp
                      base64codec.cpp
                      csvdeserializer.cpp
                      csvformatter.cpp
                      csvparser.cpp
                      char.cpp
                      charmapcodec.cpp
                      clock.cpp
                      clockimpl.cpp
                      condition.cpp
                      conditionimpl.cpp
                      connectable.cpp
                      connection.cpp
                      cgi.cpp
                      conversionerror.cpp
                      convert.cpp
                      date.cpp
                      datetime.cpp
                      dateutils.cpp
                      decomposer.cpp
                      deserializer.cpp
                      directory.cpp
                      directoryimpl.cpp
                      envsubst.cpp
                      error.cpp
                      eventloop.cpp
                      eventsink.cpp
                      eventsource.cpp
                      fdstream.cpp
                      file.cpp
                      filedevice.cpp
                      filedeviceimpl.cpp
                      fileimpl.cpp
                      fileinfo.cpp
                      formatter.cpp
                      hdstream.cpp
                      inideserializer.cpp
                      inifile.cpp
                      iniparser.cpp
                      iniserializer.cpp
                      iodevice.cpp
                      iodeviceimpl.cpp
                      ioerror.cpp
                      iostream.cpp
                      iso8859_codec.cpp
                      jsondeserializer.cpp
                      jsonformatter.cpp
                      jsonparser.cpp
                      library.cpp
                      libraryimpl.cpp
                      log.cpp
                      md5stream.cpp
                      mime.cpp
                      multifstream.cpp
                      mutex.cpp
                      muteximpl.cpp
                      pipe.cpp
                      pipeimpl.cpp
                      posix/commandinput.cpp
                      posix/commandoutput.cpp
                      posix/daemonize.cpp
                      posix/fork.cpp
                      posix/pipestream.cpp
                      posix/posixpipe.cpp
                      propertiesfile.cpp
                      propertiesparser.cpp
                      propertiesdeserializer.cpp
                      propertiesserializer.cpp
                      query_params.cpp
                      quotedprintablecodec.cpp
                      regex.cpp
                      remoteclient.cpp
                      selectable.cpp
                      selector.cpp
                      selectorimpl.cpp
                      semaphore.cpp
                      semaphoreimpl.cpp
                      serviceregistry.cpp
                      settings.cpp
                      settingsreader.cpp
                      settingswriter.cpp
                      serializationerror.cpp
                      serializationinfo.cpp
                      signal.cpp
                      sslcertificate.cpp
                      stddevice.cpp
                      streambuffer.cpp
                      string.cpp
                      stringstream.cpp
                      systemerror.cpp
                      tee.cpp
                      textbuffer.cpp
                      textcodec.cpp
                      textstream.cpp
                      thread.cpp
                      threadimpl.cpp
                      threadpool.cpp
                      threadpoolimpl.cpp
                      time.cpp
                      timer.cpp
                      timespan.cpp
                      uri.cpp
                      utf8codec.cpp
                      uuencode.cpp
                      net.cpp
                      tcpserverimpl.cpp
                      tcpserver.cpp
                      tcpsocket.cpp
                      tcpsocketimpl.cpp
                      tcpstream.cpp
                      tz.cpp
                      udp.cpp
                      udpstream.cpp
                      win1252codec.cpp
                      xml/characters.cpp
                      xml/endelement.cpp
                      xml/entityresolver.cpp
                      xml/namespacecontext.cpp
                      xml/startelement.cpp
                      xml/xmldeserializer.cpp
                      xml/xmlerror.cpp
                      xml/xmlformatter.cpp
                      xml/xmlreader.cpp
                      xml/xmlserializer.cpp
                      xml/xmlwriter.cpp
                      iconvwrap.cpp
                      iconvstream.cpp
                      sslcertificateimpl.cpp
                      sslctx.cpp
                      sslctximpl.cpp
   )

set( cxxtools_headers ${CMAKE_CURRENT_SOURCE_DIR}/../include
                      ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

add_library( cxxtools_static STATIC ${cxxtools_sources} )

set_target_properties( cxxtools_static PROPERTIES OUTPUT_NAME cxxtools )
set_target_properties( cxxtools_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxtools/lib )

#target_compile_definitions( cxxtools PRIVATE BUILT_SHARED=ON )

target_compile_options( cxxtools_static PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( cxxtools_static PRIVATE ${cxxtools_headers} )

set_target_properties( cxxtools_static PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_BUILD_DIR}/lib/cxxtools/libcxxtools.a")

set_target_properties( cxxtools_static PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${cxxtools_headers}" )

target_link_libraries( cxxtools_static -lssl -lrt -lnsl -lpthread )

add_library( cxxtools_shared SHARED ${cxxtools_sources} )

SET_TARGET_PROPERTIES( cxxtools_shared PROPERTIES OUTPUT_NAME cxxtools )
set_target_properties( cxxtools_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxtools/lib )

target_compile_options( cxxtools_shared PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( cxxtools_shared PRIVATE ${cxxtools_headers} )

set_target_properties( cxxtools_shared PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_BUILD_DIR}/lib/cxxtools/libcxxtools.so")

set_target_properties( cxxtools_shared PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${cxxtools_headers}" )

target_link_libraries( cxxtools_shared -lssl -lrt -lnsl -lpthread )

add_subdirectory(bin)