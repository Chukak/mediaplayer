## Run tests
To run the tests, run the following commands:

1. Create a directory, which will be used for testing. For example, in Linux:
```bash
mkdir testing && cd testing
```

2. Copy resources to the testing directory. For example, in Linux:
```bash
cp -R /path/to/project/tests/resources resources/
```

3. Run qmake, which has QT version 5.7 and more, use the path to the project. For example, in Linux:
```bash
qmake /path/to/project/tests/unit-tests/unit-tests.pro -spec linux-g++ 
```
* If you need a special path to qmake, (for example, in Linux: `/opt/Qt/5.9.4/gcc_64/bin/qmake`):
```bash
/path/to/qmake /path/to/project/tests/unit-tests/unit-tests.pro -spec linux-g++
```

4. Run make. For example, in Linux:
```bash
make
```
5. Copy and script for running all tests and make it executable. For example, in Linux:
```bash
cp /path/to/project/tests/unit-tests/run_tests.sh run_tests.sh
chmod +x run_tests.sh
```
6. Run all tests. For example, in Linux:
```bash
./run_tests.sh
```
### All commands 
```bash
mkdir testing && cd testing && cp -R /path/to/project/tests/resources resources/ && /path/to/qmake /path/to/project/tests/unit-tests/unit-tests.pro -spec linux-g++ && make && cp /path/to/project/tests/unit-tests/run_tests.sh run_tests.sh && chmod +x run_tests.sh && ./run_tests.sh
```

Replace `/path/to/qmake` with your qmake path, `/path/to/project/` with your project path. 

## IDE
To running tests from IDE:

1. Open unit-test.pro in your IDE.


2. Build the project and run it.

