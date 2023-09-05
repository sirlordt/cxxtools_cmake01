Run demos shared (Linux)
==============================

In the root folder project

```sh
cd build/demo
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}":../lib" ./arg_shared
```

Run test shared (Linux)
==============================

In the root folder project

```sh
cd build/test
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}":../lib" ./alltest_shared
```

or to run specific test name space. For example uri

```sh
cd build/test
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}":../lib" ./alltest_shared uri
```

output:

```sh
uri::testUri_UPHP: OK
uri::testUri_UHP: OK
uri::testUri_UPH: OK
uri::testUri_HP: OK
uri::testUri_H: OK
uri::testUri_UPH6P: OK
uri::testUri_UH6P: OK
uri::testUri_UPH6: OK
uri::testUri_H6P: OK
uri::testUri_H6: OK
uri::testQuery: OK
uri::testFragment: OK
uri::testQueryFragment: OK
uri::testHttpPort: OK
uri::testHttpsPort: OK
uri::testFtpPort: OK
uri::testUriStr: OK
```
