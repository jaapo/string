export BIN_DIR = $(PWD)/bin/

bin-dir:
	mkdir -p $(BIN_DIR)

build: bin-dir
	make -C src

build-prod: bin-dir
	make -C src build-prod

test:
	$(MAKE) -C src/test run-test

clean: bin-dir
	$(MAKE) -C src/test clean
	rm bin/*
