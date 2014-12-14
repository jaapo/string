vpath %.o $(BIN_DIR)

build-prod: CFLAGS = -DNDEBUG
build-prod: string.o

all: string.o main.o

main.o: main.cpp string.h string.o
	g++ -std=c++11 -Wall -ggdb $(CFLAGS) -o $(BIN_DIR)main.o $(BIN_DIR)string.o main.cpp

string.o: string.cpp string.h
	g++ -std=c++11 -Wall -ggdb $(CFLAGS) -c -o $(BIN_DIR)string.o string.cpp

run-test:
	$(MAKE) -C test run-test

clean:
	rm $(BIN_DIR)main.o $(BIN_DIR)string.o
