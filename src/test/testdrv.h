#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define Assert(COND) do { if(!(COND)) throw test_exception("assertion (" #COND ") failed in " __FILE__ ":" STR(__LINE__)); } while(0)
#define AssertEquals(A,B) Assert(A == B)
#define AssertNotEquals(A,B) Assert(A != B)
#define AssertThrows(FUNC) do { bool thrown___ = false; try { FUNC; } catch (...) {thrown___=true;} Assert(thrown___); } while(0)

class Test {
	private:
		std::string desc_;
		std::string result_;
		bool passed_;
		void (*testFunction)();

	public:
		Test(std::string desc, void (*testFunction)());
		~Test(){};
		Test(Test const& t);
		Test(Test&& t);
		Test& operator=(Test const& t);
		Test operator=(Test &t);

		void run();
		bool passed();
		std::string result();
		std::string desc();
};

class TestSet {
	private:
		int ran_;
		int ok_;
		int fail_;
		std::vector<Test> tests_;

	public:
		TestSet();

		void addTest(Test test);
		void runAll();
		void summary();
		void details();

		int ran();
		int ok();
		int fail();
};

class test_exception:public std::exception {
	private:
		char* msg_;

	public:
		test_exception(char* msg): msg_(msg) {};

		virtual const char* what() const throw() {
			return msg_;
		};
};
