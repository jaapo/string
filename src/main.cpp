#include <iostream>
#include "string.h"

int main() {
	//Creating strings - required:
	String str = "C-style string literal"; // is the same as: String str("C-style string literal");
	String str_2(str);
	String str_3;
	//Optional - not required:
	//String str_4 = { 'H','e','l','l','o' }; // list initializer construction

	// Using strings
	// access and modify:
	char ch = str[0]; // ch == 'C'
	str[0] = 'T';     // str[0] == 'T'
	std::cout << str.size() << std::endl; // prints: 22
	for (auto it = str.begin();it != str.end();++it)  // prints: T-style string literal
		std::cout << *it;
	str.push_back('!'); // str == String("T-style string literal!")
	char last = str.pop_back(); // last == '!'
	str_2.insert(0,'A');   // str_2 == String("AT-style string literal")
	str_3.insert(0,str_2); // str_3 == String("AT-style string literal")
	str_3.insert(str_3.size() - 1," another literal");  //str_3 == String("AT-style string literal another literal")
	str_3.erase(1,3); //str_3 == String("Atyle string literal another literal")
	str.swap(str_3);  // swap the contents with str_3

	// stream output and input
	std::cout << str_3;
	String input_str;
	std::cin >> input_str;

	std::cout << input_str << '\n';

	const String str_4(input_str);
	std::cout << str_4[0] << str_4.size() << '\n';

	String str_5 = std::move(str_2);

	std::cout << str_5 << '\n';
	std::cout << str_2 << '\n';
	return 0;
}
