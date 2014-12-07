#include <string>
#include <vector>

class Test {
	private:
		std::string name_;
		std::string desc_;
		std::string result_;
		bool passed_;
		bool (*testFunction)();

	public:
		Test(std::string name, std::string desc, bool (*testFunction)());

		void run();
		bool passed();
		std::string result();
		
		std::string name();
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
		void details(bool withDesc, bool failsOnly);

		int ran();
		int ok();
		int fail();
};
