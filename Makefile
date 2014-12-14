export BIN_DIR = $(PWD)/bin/

build:
	make -C src

build-prod:
	make -C src build-prod

test:
	$(MAKE) -C src/test run-test

clean:
	rm bin/*
	$(MAKE) -C src/test clean
