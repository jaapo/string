#include "testdrv.h"

#include <iostream>
#include <vector>

using std::string;

//Test class
Test::Test(string name, string desc, bool (*testFunction)()): 
	name_ (name),
 	desc_ (desc), 
	testFunction(testFunction) {}

void Test::run() {
	bool ret = false;

	try {
		ret = (*testFunction)();
	} catch(const std::exception &e) {
		result_ = e.what();
	}

	passed_ = ret;
}

//accessors
bool Test::passed() {
	return passed_;
}

string Test::result() {
	return result_;
}

string Test::name() {
	return name_;
}

string Test::desc() {
	return desc_;
}

//TestSet class
TestSet::TestSet(): 
	ran_(0), 
	ok_(0), 
	fail_(0), 
	tests_(std::vector<Test>()) {}

void TestSet::addTest(Test test) {
	tests_.push_back(test);
}

void TestSet::runAll() {
	ran_ = 0;
	ok_ = 0;
	fail_ = 0;

	for(auto test : tests_) {
		test.run();
		ran_++;

		if (test.passed()) {
			ok_++;
		} else {
			fail_++;
		}
	}
}

void TestSet::summary() {
	if(fail_ == 0) {
		std::cout << "all tests passed!" << std::endl;
	} else {
		std::cout << "tests failed!" << std::endl;
	}
	std::cout << std::endl;

	//markdown syntax table
	std::cout << "| tests | passed | failed | percent |" << std::endl;
	std::cout << "| ----- | ------ | ------ | ------- |" << std::endl;
	std::cout << "|" << ran_ << " | " << ok_ << " | " << fail_ << " | " << (ok_/ran_)*100 << "|" << std::endl << std::endl;
}

void TestSet::details(bool withDesc, bool failsOnly) {
	//markdown syntax table
	std::cout << "| test | status |" << (withDesc ? " description |" : "") << " error |" << std::endl;
	std::cout << "| ---- | ------ |" << (withDesc ? " ----------- |" : "") << " ---- |" << std::endl;

	for(auto test : tests_) {
		if(!test.passed() || !failsOnly) {
			std::cout 
				<< "| " << test.name() 
				<< " | " << (test.passed() ? "ok" : "fail")
				<< (withDesc ? " | " + test.desc() : "")
				<< " | " << test.result() 
				<< " |" << std::endl;
		}
	}
	std::cout << std::endl;
}
