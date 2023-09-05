set( __LIBRARY_NAME__ cxxtools-json )
set( __LIBRARY_STATIC__ "${__LIBRARY_NAME__}_static" )
set( __LIBRARY_SHARED__ "${__LIBRARY_NAME__}_shared" )
set( __LIBRARY_LINK_LIBS__ "-lssl -lrt -lnsl -lpthread" )

project( ${__LIBRARY_NAME__} VERSION ${__MAIN_LIBRARY_VERSION__} LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSION ON )

set( __LIBRARY_SOURCES__
rpcserverimpl.cpp
worker.cpp
rpcclientimpl.cpp
httpresponder.cpp
scanner.cpp
httpclient.cpp
responder.cpp
rpcserver.cpp
httpclientimpl.cpp
httpservice.cpp
socket.cpp
rpcclient.cpp
)

#message( STATUS "CMAKE_CURRENT_SOURCE_DIR => ${CMAKE_CURRENT_SOURCE_DIR}" )
#message( STATUS "CMAKE_SOURCE_DIR => ${CMAKE_SOURCE_DIR}" )

set( __LIBRARY_HEADERS_FOLDERS__ ${CMAKE_CURRENT_SOURCE_DIR}/../../include
                         ${CMAKE_CURRENT_SOURCE_DIR}/../
                         ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

#message( STATUS "CMAKE_CURRENT_BINARY_DIR => ${CMAKE_CURRENT_BINARY_DIR}" )
#message( STATUS "CMAKE_BINARY_DIR => ${CMAKE_BINARY_DIR}" )

add_library( ${__LIBRARY_STATIC__} STATIC ${__LIBRARY_SOURCES__} )

add_dependencies( ${__LIBRARY_STATIC__} ${__MAIN_LIBRARY_STATIC__} )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES OUTPUT_NAME ${__LIBRARY_NAME__} )
set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/ )

#target_compile_definitions( cxxtools PRIVATE BUILT_SHARED=ON )

target_compile_options( ${__LIBRARY_STATIC__} PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( ${__LIBRARY_STATIC__} PUBLIC ${__LIBRARY_HEADERS_FOLDERS__} )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/lib${__LIBRARY_NAME__}.a" )

set_target_properties( ${__LIBRARY_STATIC__} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__LIBRARY_HEADERS_FOLDERS__}" )

target_link_libraries( ${__LIBRARY_STATIC__} ${__LIBRARY_LINK_LIBS__} )

add_library( ${__LIBRARY_SHARED__} SHARED ${__LIBRARY_SOURCES__} )

add_dependencies( ${__LIBRARY_SHARED__} ${__MAIN_LIBRARY_SHARED__} )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES OUTPUT_NAME ${__LIBRARY_NAME__} )
set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/ )

target_compile_options( ${__LIBRARY_SHARED__} PRIVATE
                        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                        -Wall -Wpedantic>
                        $<$<CXX_COMPILER_ID:MSVC>:
                        /W4 /pedantic>)

target_include_directories( ${__LIBRARY_SHARED__} PUBLIC ${__LIBRARY_HEADERS_FOLDERS__} )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/${__MAIN_LIBRARY_OUTPUT_PATH__}/lib${__LIBRARY_NAME__}.so" )

set_target_properties( ${__LIBRARY_SHARED__} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${__LIBRARY_HEADERS_FOLDERS__}" )

target_link_libraries( ${__LIBRARY_SHARED__} ${__LIBRARY_LINK_LIBS__} )

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
