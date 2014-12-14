#include "testdrv.h"

#include <iostream>
#include <vector>

using std::string;

//Test class
Test::Test(string desc, void (*testFunction)()): 
 	desc_ (desc), 
	testFunction(testFunction),
	passed_(false) {}

Test::Test(Test const& t): 
 	desc_ (t.desc_), 
	testFunction(t.testFunction),
	passed_(t.passed_),
	result_(t.result_){
		//std::cout<< "ctor called " << t.desc_ << '\n';
	}

Test::Test(Test&& t): 
 	desc_ (t.desc_), 
	testFunction(t.testFunction),
	passed_(t.passed_),
	result_(t.result_){
		//std::cout<< "ctor&& called " << t.desc_ << '\n';
	}

Test& Test::operator=(Test const& t) {
	desc_ = t.desc_;
	testFunction = t.testFunction;
	passed_ = t.passed_;
	result_ = t.result_;
	//std::cout << "copy assignment called " << t.desc_ << '\n';
}

Test Test::operator=(Test &t) {
	desc_ = t.desc_;
	testFunction = t.testFunction;
	passed_ = t.passed_;
	result_ = t.result_;
	//std::cout << "move assignment called " << t.desc_ << '\n';
}


void Test::run() {
	bool ret = true;

	try {
		(*testFunction)();
	} catch(const std::exception &e) {
		result_ = std::string("Exception thrown: ") + std::string(e.what());
		ret = false;
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

	for(auto& test : tests_) {
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
	std::cout << "Test summary" << std::endl;
	std::cout << "============" << std::endl;

	if(fail_ == 0) {
		std::cout << "all tests passed!" << std::endl;
	} else {
		std::cout << "tests failed!" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "tests: " << ran_ << std::endl;
	std::cout << "passed: " << ok_ << std::endl;
	std::cout << "failed: " << fail_ << std::endl;
}

void TestSet::details() {
	for(auto& test : tests_) {
			std::cout 
				<< (test.passed() ? "ok    " : "fail  ")
				<< test.desc() << std::endl;
			if (!test.passed()) {
				std::cout << "  ===>    " << test.result() << std::endl;
			}
	}
	std::cout << std::endl;
}
