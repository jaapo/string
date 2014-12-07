export BIN_DIR = $(PWD)/bin/

build:
	make -C src

test:
	$(MAKE) -C src/test run-test

clean:
	rm bin/*
