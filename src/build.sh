#!/bin/bash

files_cpp=(
"addrinfo.cpp"
"addrinfoimpl.cpp"
"application.cpp"
"applicationimpl.cpp"
"base64codec.cpp"
"csvdeserializer.cpp"
"csvformatter.cpp"
"csvparser.cpp"
"char.cpp"
"charmapcodec.cpp"
"clock.cpp"
"clockimpl.cpp"
"condition.cpp"
"conditionimpl.cpp"
"connectable.cpp"
"connection.cpp"
"cgi.cpp"
"conversionerror.cpp"
"convert.cpp"
"date.cpp"
"datetime.cpp"
"dateutils.cpp"
"decomposer.cpp"
"deserializer.cpp"
"directory.cpp"
"directoryimpl.cpp"
"envsubst.cpp"
"error.cpp"
"eventloop.cpp"
"eventsink.cpp"
"eventsource.cpp"
"fdstream.cpp"
"file.cpp"
"filedevice.cpp"
"filedeviceimpl.cpp"
"fileimpl.cpp"
"fileinfo.cpp"
"formatter.cpp"
"hdstream.cpp"
"inideserializer.cpp"
"inifile.cpp"
"iniparser.cpp"
"iniserializer.cpp"
"iodevice.cpp"
"iodeviceimpl.cpp"
"ioerror.cpp"
"iostream.cpp"
"iso8859_codec.cpp"
"jsondeserializer.cpp"
"jsonformatter.cpp"
"jsonparser.cpp"
"library.cpp"
"libraryimpl.cpp"
"log.cpp"
"md5stream.cpp"
"mime.cpp"
"multifstream.cpp"
"mutex.cpp"
"muteximpl.cpp"
"pipe.cpp"
"pipeimpl.cpp"
"posix/commandinput.cpp"
"posix/commandoutput.cpp"
"posix/daemonize.cpp"
"posix/fork.cpp"
"posix/pipestream.cpp"
"posix/posixpipe.cpp"
"propertiesfile.cpp"
"propertiesparser.cpp"
"propertiesdeserializer.cpp"
"propertiesserializer.cpp"
"query_params.cpp"
"quotedprintablecodec.cpp"
"regex.cpp"
"remoteclient.cpp"
"selectable.cpp"
"selector.cpp"
"selectorimpl.cpp"
"semaphore.cpp"
"semaphoreimpl.cpp"
"serviceregistry.cpp"
"settings.cpp"
"settingsreader.cpp"
"settingswriter.cpp"
"serializationerror.cpp"
"serializationinfo.cpp"
"signal.cpp"
"sslcertificate.cpp"
"stddevice.cpp"
"streambuffer.cpp"
"string.cpp"
"stringstream.cpp"
"systemerror.cpp"
"tee.cpp"
"textbuffer.cpp"
"textcodec.cpp"
"textstream.cpp"
"thread.cpp"
"threadimpl.cpp"
"threadpool.cpp"
"threadpoolimpl.cpp"
"time.cpp"
"timer.cpp"
"timespan.cpp"
"uri.cpp"
"utf8codec.cpp"
"uuencode.cpp"
"net.cpp"
"tcpserverimpl.cpp"
"tcpserver.cpp"
"tcpsocket.cpp"
"tcpsocketimpl.cpp"
"tcpstream.cpp"
"tz.cpp"
"udp.cpp"
"udpstream.cpp"
"win1252codec.cpp"
"xml/characters.cpp"
"xml/endelement.cpp"
"xml/entityresolver.cpp"
"xml/namespacecontext.cpp"
"xml/startelement.cpp"
"xml/xmldeserializer.cpp"
"xml/xmlerror.cpp"
"xml/xmlformatter.cpp"
"xml/xmlreader.cpp"
"xml/xmlserializer.cpp"
"xml/xmlwriter.cpp"
"iconvwrap.cpp"
"iconvstream.cpp"
"sslcertificateimpl.cpp"
"sslctx.cpp"
"sslctximpl.cpp"
)


mkdir -p ../build/libcxxtools

rm -f ../build/libcxxtools/libcxxtools.a

files_static_lib=""

for file in ${files_cpp[@]}; do

  only_file_name="$(basename ${file} .cpp)"

  echo "Compiling: "${only_file_name}

#  g++ -DHAVE_CONFIG_H -I. -I../src -I../include -Wno-long-long -Wall -pedantic -g -c -o ${file}.o ${file}.cpp
  g++ -DHAVE_CONFIG_H -I. -I../include -Wno-long-long -Wall -pedantic -g -c -o ../build/libcxxtools/${only_file_name}.o ${file}

  files_static_lib=${files_static_lib}" "${only_file_name}.o

done

#echo ${files_static_lib}

files_c=(
"md5.c"
)

for file in ${files_c[@]}; do

  only_file_name="$(basename ${file} .c)"

  echo "Compiling: "${only_file_name}

  g++ -DHAVE_CONFIG_H -I. -I../include -Wno-long-long -Wall -pedantic -g -c -o ../build/libcxxtools/${only_file_name}.o ${file}

  files_static_lib=${files_static_lib}" "${only_file_name}.o

done

echo ${files_static_lib}

cd ../build/libcxxtools/

ar rvs libcxxtools.a ${files_static_lib}
