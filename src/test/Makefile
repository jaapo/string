vpath %.o $(BIN_DIR)
TEST_BIN_DIR = bin/
BIN_FILES = bin/testdrv.o bin/string-test
MARKDOWN = $(shell which markdown)
ifdef MARKDOWN
TEST_RESULT = $(TEST_BIN_DIR)result.html
else
TEST_RESULT = $(TEST_BIN_DIR)result.md
endif

all: testdrv.o

testdrv.o: testdrv.cpp
	g++ -std=c++11 -Wall -c -o $(TEST_BIN_DIR)testdrv.o testdrv.cpp

string-test: string-test.cpp testdrv.o
	g++ -std=c++11 -Wall -o $(TEST_BIN_DIR)string-test $(TEST_BIN_DIR)testdrv.o string-test.cpp

run-test: string-test
ifdef MARKDOWN
	bin/string-test | $(MARKDOWN) >$(TEST_RESULT)
else
	bin/string-test >$(TEST_RESULT)
endif
	@echo Test results in $(TEST_RESULT)

clean:
	rm $(BIN_FILES)
