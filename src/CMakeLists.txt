set( __MAIN_LIBRARY_OUTPUT_PATH__ lib )
set( __MAIN_LIBRARY_INSTALL_LIB_PATH__ lib )
set( __MAIN_LIBRARY_INSTALL_INCLUDE_PATH__ include )
set( __MAIN_LIBRARY_NAME__ cxxtools )

set( __LIBRARY_NAME__ cxxtools )
set( __LIBRARY_STATIC__ "${__LIBRARY_NAME__}_static" )
set( __LIBRARY_SHARED__ "${__LIBRARY_NAME__}_shared" )
set( __LIBRARY_LINK_LIBS__ "-lssl -lrt -lnsl -lpthread" )

project( ${__LIBRARY_NAME__} VERSION 3.1 LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSION ON )

set( __LIBRARY_SOURCES__
addrinfo.cpp addrinfoimpl.cpp application.cpp applicationimpl.cpp base64codec.cpp
csvdeserializer.cpp csvformatter.cpp csvparser.cpp char.cpp charmapcodec.cpp clock.cpp
clockimpl.cpp condition.cpp conditionimpl.cpp connectable.cpp connection.cpp cgi.cpp
conversionerror.cpp convert.cpp date.cpp datetime.cpp dateutils.cpp decomposer.cpp
deserializer.cpp directory.cpp directoryimpl.cpp envsubst.cpp error.cpp eventloop.cpp
eventsink.cpp eventsource.cpp fdstream.cpp file.cpp filedevice.cpp filedeviceimpl.cpp
fileimpl.cpp fileinfo.cpp formatter.cpp hdstream.cpp inideserializer.cpp inifile.cpp
iniparser.cpp iniserializer.cpp iodevice.cpp iodeviceimpl.cpp ioerror.cpp iostream.cpp
iso8859_codec.cpp jsondeserializer.cpp jsonformatter.cpp jsonparser.cpp library.cpp
libraryimpl.cpp log.cpp md5stream.cpp mime.cpp multifstream.cpp mutex.cpp muteximpl.cpp
pipe.cpp pipeimpl.cpp posix/commandinput.cpp posix/commandoutput.cpp posix/daemonize.cpp
posix/fork.cpp posix/pipestream.cpp posix/posixpipe.cpp propertiesfile.cpp propertiesparser.cpp
propertiesdeserializer.cpp propertiesserializer.cpp query_params.cpp quotedprintablecodec.cpp
regex.cpp remoteclient.cpp selectable.cpp selector.cpp selectorimpl.cpp semaphore.cpp semaphoreimpl.cpp
serviceregistry.cpp settings.cpp settingsreader.cpp settingswriter.cpp serializationerror.cpp
serializationinfo.cpp signal.cpp sslcertificate.cpp stddevice.cpp streambuffer.cpp string.cpp
stringstream.cpp systemerror.cpp tee.cpp textbuffer.cpp textcodec.cpp textstream.cpp thread.cpp
threadimpl.cpp threadpool.cpp threadpoolimpl.cpp time.cpp timer.cpp timespan.cpp uri.cpp
utf8codec.cpp uuencode.cpp net.cpp tcpserverimpl.cpp tcpserver.cpp tcpsocket.cpp tcpsocketimpl.cpp
tcpstream.cpp tz.cpp udp.cpp udpstream.cpp win1252codec.cpp xml/characters.cpp xml/endelement.cpp
xml/entityresolver.cpp xml/namespacecontext.cpp xml/startelement.cpp xml/xmldeserializer.cpp
xml/xmlerror.cpp xml/xmlformatter.cpp xml/xmlreader.cpp xml/xmlserializer.cpp xml/xmlwriter.cpp
iconvwrap.cpp iconvstream.cpp sslcertificateimpl.cpp sslctx.cpp sslctximpl.cpp md5.c
)

#message( STATUS "CMAKE_CURRENT_SOURCE_DIR => ${CMAKE_CURRENT_SOURCE_DIR}" )
#message( STATUS "CMAKE_SOURCE_DIR => ${CMAKE_SOURCE_DIR}" )

set( __LIBRARY_HEADERS_FOLDERS__ ${CMAKE_CURRENT_SOURCE_DIR}/../include
                                 ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

#file( GLOB_RECURSE __LIBRARY_HEADERS_FILES__ ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h
#                                             ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.tpp )

#message( STATUS "__LIBRARY_HEADERS_FILES__ => ${__LIBRARY_HEADERS_FILES__}" )

#message( STATUS "CMAKE_CURRENT_BINARY_DIR => ${CMAKE_CURRENT_BINARY_DIR}" )
#message( STATUS "CMAKE_BINARY_DIR => ${CMAKE_BINARY_DIR}" )

add_library( ${__LIBRARY_STATIC__} STATIC ${__LIBRARY_SOURCES__} )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES OUTPUT_NAME ${__LIBRARY_NAME__} )
set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/ )
#set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES PUBLIC_HEADER "${__LIBRARY_HEADERS_FILES__}" )

#target_compile_definitions( cxxtools PRIVATE BUILT_SHARED=ON )

target_compile_options( ${__LIBRARY_STATIC__} PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( ${__LIBRARY_STATIC__} PUBLIC ${__LIBRARY_HEADERS_FOLDERS__} )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/${__LIBRARY_OUTPUT_PATH__}/lib${__LIBRARY_NAME__}.a" )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__LIBRARY_HEADERS_FOLDERS__}" )

target_link_libraries( ${__LIBRARY_STATIC__} ${__LIBRARY_LINK_LIBS__} )

add_library( ${__LIBRARY_SHARED__} SHARED ${__LIBRARY_SOURCES__} )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES OUTPUT_NAME ${__LIBRARY_NAME__} )
set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/ )
#set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES PUBLIC_HEADER ${__LIBRARY_HEADERS_FILES__} );

target_compile_options( ${__LIBRARY_SHARED__} PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( ${__LIBRARY_SHARED__} PUBLIC ${__LIBRARY_HEADERS_FOLDERS__} )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/${__LIBRARY_OUTPUT_PATH__}/lib${__LIBRARY_NAME__}.so" )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__LIBRARY_HEADERS_FOLDERS__}" )

target_link_libraries( ${__LIBRARY_SHARED__} ${__LIBRARY_LINK_LIBS__} )

#message( STATUS "CMAKE_INSTALL_LIBDIR => ${CMAKE_INSTALL_LIBDIR}" )

install(
  TARGETS ${__LIBRARY_STATIC__}
  LIBRARY DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
  ARCHIVE DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
  RUNTIME DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
)

install(
  TARGETS ${__LIBRARY_SHARED__}
  LIBRARY DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
  ARCHIVE DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
  RUNTIME DESTINATION ${__MAIN_LIBRARY_INSTALL_LIB_PATH__}
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../include/" # source directory
        DESTINATION ${__MAIN_LIBRARY_INSTALL_INCLUDE_PATH__} # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
        PATTERN "*.tpp" # additional header files
)

add_subdirectory(bin)
add_subdirectory(http)
add_subdirectory(json)
add_subdirectory(unit)
add_subdirectory(xmlrpc)