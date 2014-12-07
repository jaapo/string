#include "testdrv.h"

#include <stdexcept>
#include <vector>
#include <iostream>

bool ifailtest() {
	return false;
}

bool ithrow() {
	throw std::logic_error("thrown by ithrow");
}

int main() {
	TestSet tests;
	tests.addTest(Test("thrower", "test the thrower", ithrow));
	tests.addTest(Test("failer", "test the failer", ifailtest));
	tests.runAll();

	tests.summary();

	tests.details(true, true);
}
