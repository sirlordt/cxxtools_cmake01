project( cxxtools-bin VERSION 3.1 LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSION ON )

set( cxxtools-bin_sources serializer.cpp
                          parser.cpp
                          rpcserverimpl.cpp
                          deserializer.cpp
                          worker.cpp
                          rpcclientimpl.cpp
                          scanner.cpp
                          formatter.cpp
                          responder.cpp
                          rpcserver.cpp
                          socket.cpp
                          rpcclient.cpp
   )

set( cxxtools-bin_headers ${CMAKE_CURRENT_SOURCE_DIR}/../../include
                          ${CMAKE_CURRENT_SOURCE_DIR}/../
                          ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

add_library( cxxtools-bin_static STATIC ${cxxtools-bin_sources} )

set_target_properties( cxxtools-bin_static PROPERTIES OUTPUT_NAME cxxtools-bin )
set_target_properties( cxxtools-bin_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxtools/lib )

#target_compile_definitions( cxxtools PRIVATE BUILT_SHARED=ON )

target_compile_options( cxxtools-bin_static PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( cxxtools-bin_static PRIVATE ${cxxtools_headers} )

set_target_properties( cxxtools-bin_static PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_BUILD_DIR}/lib/cxxtools/libcxxtools-bin.a")

set_target_properties( cxxtools-bin_static PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${cxxtools-bin_headers}" )

target_link_libraries( cxxtools-bin_static -l./libcxxtools.a -lssl -lrt -lnsl -lpthread )

add_library( cxxtools-bin_shared SHARED ${cxxtools-bin_sources} )

SET_TARGET_PROPERTIES( cxxtools-bin_shared PROPERTIES OUTPUT_NAME cxxtools )
set_target_properties( cxxtools-bin_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxtools/lib )

target_compile_options( cxxtools-bin_shared PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( cxxtools-bin_shared PRIVATE ${cxxtools_headers} )

set_target_properties( cxxtools-bin_shared PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_BUILD_DIR}/lib/cxxtools/libcxxtools-bin.so")

set_target_properties( cxxtools-bin_shared PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${cxxtools-bin_headers}" )

target_link_libraries( cxxtools-bin_shared -l./libcxxtools.so -lssl -lrt -lnsl -lpthread )
