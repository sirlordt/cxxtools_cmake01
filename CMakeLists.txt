cmake_minimum_required( VERSION 3.15 )

set( __MAIN_LIBRARY_OUTPUT_PATH__ lib )
set( __MAIN_LIBRARY_INSTALL_LIB_PATH__ lib )
set( __MAIN_LIBRARY_INSTALL_INCLUDE_PATH__ include )
set( __MAIN_LIBRARY_NAME__ cxxtools )
set( __MAIN_LIBRARY_VERSION__ 3.1 )

set( __MAIN_LIBRARY_STATIC__ "${__MAIN_LIBRARY_NAME__}_static" )
set( __MAIN_LIBRARY_SHARED__ "${__MAIN_LIBRARY_NAME__}_shared" )
set( __MAIN_LIBRARY_LINK_LIBS__ "-lssl -lrt -lnsl -lpthread" )

project( ${__MAIN_LIBRARY_NAME__} VERSION ${__MAIN_LIBRARY_VERSION__} LANGUAGES C CXX )

#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSION ON)

set( CMAKE_VERBOSE_MAKEFILE ON )

#set(CMAKE_FIND_LIBRARY_SUFFIX ".a")
#set(CMAKE_BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/libs)

option( BUILD_DEMO "build demos in folder demo" OFF )
option( BUILD_TOOLS "build tools in folder tools" ON )
option( BUILD_TEST "build test in folder test" OFF )

add_subdirectory( src )

if ( BUILD_DEMO )

  add_subdirectory( demo )

endif()

if ( BUILD_TOOLS )

  add_subdirectory( tools )

endif()

if ( BUILD_TEST )

  add_subdirectory( test )

endif()
