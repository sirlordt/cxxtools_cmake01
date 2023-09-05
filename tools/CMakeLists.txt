set( __PROJECT_NAME__ cxxtools-tools )

project( ${__PROJECT_NAME__} VERSION ${__MAIN_LIBRARY_VERSION__} LANGUAGES C CXX )

set( __DEMO_LINK_LIBS__ "-lssl -lcrypto -lrt -lnsl -lpthread" )

set(CMAKE_FIND_LIBRARY_SUFFIX ".a")
set(CMAKE_BUILD_SHARED_LIBS OFF)

set( __DEMO_HEADERS_FOLDERS__ ${CMAKE_CURRENT_SOURCE_DIR}/../include
                              ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

file( GLOB_RECURSE __DEMO_SOURCES__ ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

foreach( __DEMO_SOURCE_FILE__ ${__DEMO_SOURCES__} )

  # Cut off the file extension and directory path
  get_filename_component( __DEMO_NAME__ ${__DEMO_SOURCE_FILE__} NAME_WE )

  add_executable( ${__DEMO_NAME__}_static ${__DEMO_SOURCE_FILE__} )

  target_include_directories( ${__DEMO_NAME__}_static PUBLIC ${__DEMO_HEADERS_FOLDERS__} )

  target_link_options( ${__DEMO_NAME__}_static PUBLIC "-static" )

  # Make sure YourLib is linked to each app
  target_link_libraries( ${__DEMO_NAME__}_static -L${CMAKE_BINARY_DIR}/lib -Wl,--start-group -l:libcxxtools-bin.a -l:libcxxtools-unit.a -l:libcxxtools-xmlrpc.a -l:libcxxtools-json.a -l:libcxxtools-http.a -l:libcxxtools.a -Wl,--end-group ${__DEMO_LINK_LIBS__}  )

  add_executable( ${__DEMO_NAME__}_shared ${__DEMO_SOURCE_FILE__} )

  target_include_directories( ${__DEMO_NAME__}_shared PUBLIC ${__DEMO_HEADERS_FOLDERS__} )

  # Make sure YourLib is linked to each app
  target_link_libraries( ${__DEMO_NAME__}_shared -L${CMAKE_BINARY_DIR}/lib -l:libcxxtools-bin.so -l:libcxxtools-unit.so -l:libcxxtools-xmlrpc.so -l:libcxxtools-json.so -l:libcxxtools-http.so -l:libcxxtools.so ${__DEMO_LINK_LIBS__} )

endforeach( __DEMO_SOURCE_FILE__ ${__DEMO_SOURCES__} )