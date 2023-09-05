set( __PROJECT_NAME__ cxxtools-test )

project( ${__PROJECT_NAME__} VERSION ${__MAIN_LIBRARY_VERSION__} LANGUAGES C CXX )

set( __TEST_LINK_LIBS__ "-lssl -lcrypto -lrt -lnsl -lpthread" )

set(CMAKE_FIND_LIBRARY_SUFFIX ".a")
set(CMAKE_BUILD_SHARED_LIBS OFF)

set( __TEST_HEADERS_FOLDERS__ ${CMAKE_CURRENT_SOURCE_DIR}/../include
                              ${CMAKE_CURRENT_SOURCE_DIR}/../src
                              ${CMAKE_CURRENT_SOURCE_DIR}/.
   )

#file( GLOB_RECURSE __DEMO_SOURCES__ ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
set( __ALLTEST_SOURCES__
arg-test.cpp
base64-test.cpp
binrpc-test.cpp
binserializer-test.cpp
cache-test.cpp
char-test.cpp
clock-test.cpp
csvdeserializer-test.cpp
csvserializer-test.cpp
convert-test.cpp
date-test.cpp
datetime-test.cpp
directory-test.cpp
envsubst-test.cpp
eventloop-test.cpp
file-test.cpp
fileinfo-test.cpp
inifile-test.cpp
iniparser-test.cpp
iniserialization-test.cpp
iso8859_1-test.cpp
iso8859_15-test.cpp
join-test.cpp
json-test.cpp
jsondeserializer-test.cpp
jsonrpc-test.cpp
jsonrpchttp-test.cpp
jsonserializer-test.cpp
limitstream-test.cpp
logconfiguration-test.cpp
lrucache-test.cpp
mime-test.cpp
md5-test.cpp
pool-test.cpp
properties-test.cpp
propertiesserializer-test.cpp
ptrstream-test.cpp
query_params-test.cpp
quotedprintable-test.cpp
regex-test.cpp
scopedincrement-test.cpp
serialization-test.cpp
serializationinfo-test.cpp
smartptr-test.cpp
split-test.cpp
string-test.cpp
test-main.cpp
time-test.cpp
timespan-test.cpp
trim-test.cpp
tz-test.cpp
utf8-test.cpp
uri-test.cpp
win1252-test.cpp
xmlreader-test.cpp
xmlrpc-test.cpp
xmlrpccallback-test.cpp
xmldeserializer-test.cpp
xmlserializer-test.cpp
)

add_executable( alltest_static ${__ALLTEST_SOURCES__} )

target_include_directories( alltest_static PUBLIC ${__TEST_HEADERS_FOLDERS__} )

target_link_options( alltest_static PUBLIC "-static" )

# Make sure YourLib is linked to each app
target_link_libraries( alltest_static -L${CMAKE_BINARY_DIR}/lib -Wl,--start-group -l:libcxxtools-bin.a -l:libcxxtools-unit.a -l:libcxxtools-xmlrpc.a -l:libcxxtools-json.a -l:libcxxtools-http.a -l:libcxxtools.a -Wl,--end-group ${__TEST_LINK_LIBS__} )

add_executable( alltest_shared ${__ALLTEST_SOURCES__} )

target_include_directories( alltest_shared PUBLIC ${__TEST_HEADERS_FOLDERS__} )

# Make sure YourLib is linked to each app
target_link_libraries( alltest_shared -L${CMAKE_BINARY_DIR}/lib -Wl,--start-group -l:libcxxtools-bin.so -l:libcxxtools-unit.so -l:libcxxtools-xmlrpc.so -l:libcxxtools-json.so -l:libcxxtools-http.so -l:libcxxtools.so -Wl,--end-group ${__TEST_LINK_LIBS__}  )

#cgitest.cpp
#query_params_test.cpp

set( __TEST_SOURCES__
logbench.cpp
rpcbenchasyncclient.cpp
rpcbenchclient.cpp
rpcbenchserver.cpp
serializer-bench.cpp
)

foreach( __TEST_SOURCE_FILE__ ${__TEST_SOURCES__} )

  # Cut off the file extension and directory path
  get_filename_component( __TEST_NAME__ ${__TEST_SOURCE_FILE__} NAME_WE )

  add_executable( ${__TEST_NAME__}_static ${__TEST_SOURCE_FILE__} )

  target_include_directories( ${__TEST_NAME__}_static PUBLIC ${__TEST_HEADERS_FOLDERS__} )

  target_link_options( ${__TEST_NAME__}_static PUBLIC "-static" )

  # Make sure YourLib is linked to each app
  target_link_libraries( ${__TEST_NAME__}_static -L${CMAKE_BINARY_DIR}/lib -Wl,--start-group -l:libcxxtools-bin.a -l:libcxxtools-unit.a -l:libcxxtools-xmlrpc.a -l:libcxxtools-json.a -l:libcxxtools-http.a -l:libcxxtools.a -Wl,--end-group ${__TEST_LINK_LIBS__}  )

  add_executable( ${__TEST_NAME__}_shared ${__TEST_SOURCE_FILE__} )

  target_include_directories( ${__TEST_NAME__}_shared PUBLIC ${__TEST_HEADERS_FOLDERS__} )

  # Make sure YourLib is linked to each app
  target_link_libraries( ${__TEST_NAME__}_shared -L${CMAKE_BINARY_DIR}/lib -l:libcxxtools-bin.so -l:libcxxtools-unit.so -l:libcxxtools-xmlrpc.so -l:libcxxtools-json.so -l:libcxxtools-http.so -l:libcxxtools.so ${__TEST_LINK_LIBS__} )

endforeach( __TEST_SOURCE_FILE__ ${__TEST_SOURCES__} )