vpath %.o $(BIN_DIR)
TEST_BIN_DIR = bin/
BIN_FILES = bin/testdrv.o bin/string-test

all: testdrv.o

testdrv.o: testdrv.cpp
	g++ -std=c++11 -ggdb -Wno-write-strings -c -o $(TEST_BIN_DIR)testdrv.o testdrv.cpp

string-test: string-test.cpp testdrv.o
	g++ -std=c++11 -ggdb -Wno-write-strings -DTEST -o $(TEST_BIN_DIR)string-test $(TEST_BIN_DIR)testdrv.o string-test.cpp ../string.cpp

string-test-prod: string-test.cpp testdrv.o
	g++ -std=c++11 -ggdb -Wno-write-strings -o $(TEST_BIN_DIR)string-test-prod $(TEST_BIN_DIR)testdrv.o string-test.cpp ../string.cpp

string-test-prod-run: string-test-prod
	$(TEST_BIN_DIR)/string-test-prod

run-test: string-test
	bin/string-test

clean:
	rm $(BIN_FILES)
