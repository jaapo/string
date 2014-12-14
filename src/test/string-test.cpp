#include "testdrv.h"

#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>

#include "../string.h"


void ifailtest() {
	Assert(false);
}

void ithrow() {
	throw std::logic_error("thrown by ithrow");
}

void testStringZeroArgCtor() {
	String s;
	AssertEquals(s.size(), 0);
}

void testStringSizeCtor() {
	String s(6);
	AssertEquals(s.size(), 0);
}

void testStringLiteralCtor() {
	String s("test");
	AssertEquals(s.size(), 4);

	s = "test";
	AssertEquals(s.size(), 4);

	String s2("");
	AssertEquals(s2.size(), 0);

	s = "";
	AssertEquals(s.size(), 0);
}

void testStringCopyCtor() {
	const String s = "test";
	String s2(s);
	AssertEquals(s2[0], 't');
	AssertEquals(s2.size(), 4);
}

void testStringMoveCtor() {
	String s = "test";
	String s2(std::move(s));

	AssertEquals(s2[0], 't');
	AssertEquals(s2.size(), 4);
	AssertEquals(s.size(), 0);
}

void testPlusOp() {
	String s = "abc";
	String s2 = "def";
	String s3 = s + s2;

	AssertEquals(s3.size(), 6);
	AssertEquals(s3[0], 'a');
	AssertEquals(s3[5], 'f');
}

void testSingleCharPlusEquOp() {
	String s = "banan";
	s += 'a';
	AssertEquals(s.size(), 6);
	AssertEquals(s[5], 'a');
}

void testStringPlusEquOp() {
	String s = "oo";
	String s2 = "aa";
	s += s2;
	AssertEquals(s.size(), 4);
	AssertEquals(s[3], 'a');
}

void testSquareBracketOpRead() {
	String s = "c++89";
	AssertEquals(s[4], '9');
	AssertEquals(s[0], 'c');

	s[4] = '1';
	s[3] = '1';
	AssertEquals(s[4], '1');
}

void testSquareBracketOpWrite() {
	String s = "c++89";

	s[4] = '1';
	s[3] = '1';
	AssertEquals(s[4], '1');
	AssertEquals(s[3], '1');
}

void testSquareBracketOpThrow() {
	String empty;
	AssertThrows(empty[0]);
	AssertThrows(empty[10]);
	AssertThrows(empty[-1]);

	String s = "c++89";
	AssertThrows(s[5]);
	AssertThrows(s[6] = 'x');
	AssertThrows(s[5] = 'a');
}

void testConstSquareBracketOp() {
	const String s = "abd";
	AssertEquals(s[0], 'a');
}

void testPushBack() {
	String s;
	s.push_back('1');
	s.push_back('2');
	s.push_back('3');
	s.push_back('4');
	AssertEquals(s.size(), 4);
	AssertEquals(s[2], '3');
}

void testPopBack() {
	String s = "abd";
	AssertEquals('d', s.pop_back());
	AssertEquals('b', s.pop_back());
}

void testPopBackThrow() {
	String s = "a";
	s.pop_back();
	AssertThrows(s.pop_back());
}

void testInsertChar() {
	String s = "";
	s.insert(0, 'X');

	AssertEquals(s.size(), 1);
	s.insert(0, 'x');
	AssertEquals(s.size(), 2);
	AssertEquals(s[0], 'x');
	AssertEquals(s[1], 'X');

	s = "aaaa";
	s.insert(2, 'b');
	AssertEquals(s[2], 'b');
	AssertEquals(s.size(), 5);
}

void testInsertCharString() {
	String s = "";
	s.insert(0, "ppp");

	AssertEquals(s.size(), 3);
	s.insert(2, "abc");
	AssertEquals(s.size(), 6);
	AssertEquals(s[0], 'p');
	AssertEquals(s[2], 'a');

	s = "aaaa";
	s.insert(4, "432");
	AssertEquals(s[2], 'a');
	AssertEquals(s[6], '2');
	AssertEquals(s.size(), 7);
}

void testInsertString() {
	String s = "";
	String ppp = "ppp";
	String abc = "abc";
	String num = "432";
	s.insert(0, ppp);

	AssertEquals(s.size(), 3);
	s.insert(2, abc);
	AssertEquals(s.size(), 6);
	AssertEquals(s[0], 'p');
	AssertEquals(s[2], 'a');

	s = "aaaa";
	s.insert(4, num);
	AssertEquals(s[2], 'a');
	AssertEquals(s[6], '2');
	AssertEquals(s.size(), 7);
}

void testInsertThrows() {
	String s = "";

	AssertThrows(s.insert(-1, 'a'));
	AssertThrows(s.insert(-1, String("aaaa")));
	AssertThrows(s.insert(-1, "pie"));
	AssertThrows(s.insert(1, 'a'));
	AssertThrows(s.insert(1, String("aaaa")));
	AssertThrows(s.insert(1, "pie"));

	s = "oooooooo";

	AssertThrows(s.insert(11, 'a'));
	AssertThrows(s.insert(11, String("aaaa")));
	AssertThrows(s.insert(11, "pie"));
	AssertThrows(s.insert(9, 'a'));
	AssertThrows(s.insert(9, String("aaaa")));
	AssertThrows(s.insert(9, "pie"));
}

void testErase() {
	String s = "ABCDEFG";
	s.erase(3,5);
	AssertEquals(s.size(), 4);
	AssertEquals(s[0], 'A');
	AssertEquals(s[3], 'G');
	AssertEquals(s[2], 'C');

	s.erase(1,3);
	AssertEquals(s.size(), 1);
	AssertEquals(s[0], 'A');
	s = "123";
	s.erase(2,2);
	AssertEquals(s.size(), 2);
	AssertEquals(s[0], '1');
	AssertEquals(s[1], '2');
}

void testEraseThrows() {
	String s = "mehem";
	AssertThrows(s.erase(3,1););
	AssertThrows(s.erase(6,6););
	AssertThrows(s.erase(-1,2););
	AssertThrows(s.erase(0,30););
	AssertThrows(s.erase(1,7););
	AssertThrows(s.erase(9,10););
}

void testSwap() {
	String s = "mehem";
	String s2 = "aham";
	s.swap(s2);

	AssertEquals(s.size(), 4);
	AssertEquals(s2.size(), 5);
	AssertEquals(s[0], 'a');
	AssertEquals(s2[0], 'm');
}

void testCString() {
	String s = "fffu";
	char* cs = s.to_C_string();
	AssertEquals(cs[0], 'f');
	AssertEquals(cs[3], 'u');
	AssertEquals(cs[4], '\0');

	delete [] cs;
}

void testStreamOutput() {
	String s = "piepie";
	std::stringstream ss;
	ss << s;
	char t;
	ss >> t;
	AssertEquals(t, 'p');
	ss >> t;
	AssertEquals(t, 'i');
	ss >> t;
	AssertEquals(t, 'e');
	ss >> t;
	AssertEquals(t, 'p');
	ss >> t;
	AssertEquals(t, 'i');
	ss >> t;
	AssertEquals(t, 'e');
	ss >> t;
	Assert(ss.fail());
}

void testStreamInput() {
	String s;
	std::stringstream ss;
	ss << 't' << 'e' << 's' << 't';
	ss >> s;
	AssertEquals(s[0], 't');
	AssertEquals(s.size(), 4);
}

void testIterators() {
	String s = "qwertyuiop";
	int i = 0;
	String::iterator b = s.begin();
	String::iterator e = s.end();
	AssertEquals(*b, 'q');
	AssertNotEquals(b, e);
	
	Assert(b == b);
	Assert(e == e);

	while(b != e) {
		e--;
		AssertEquals(*b++, s[i++]);
	}
	AssertEquals(b, e);
	AssertEquals(*b, s[5]);

	while(b != s.begin() && e != s.end()) {
		++e;
		--b;
	}
}

void testIteratorsThrow() {
	String s = "sssss";
	String::iterator b = s.begin();
	String::iterator e = s.end();

	AssertThrows(*e);
	AssertThrows(b--);
	AssertThrows(--b);
	AssertThrows(++e);
}

int main() {
	TestSet tests;
	tests.addTest(Test("string zero arg ctor returns a string with 0 size", testStringZeroArgCtor));
	tests.addTest(Test("string size ctor returns a string with 0 size", testStringSizeCtor));
	tests.addTest(Test("string literal ctor creates object with correct size()", testStringLiteralCtor));
	tests.addTest(Test("string copy ctor copies contents", testStringCopyCtor));
	tests.addTest(Test("string move ctor moves contents", testStringMoveCtor));
	tests.addTest(Test("+ operator creates new concatenated string", testPlusOp));
	tests.addTest(Test("+= operator with singl character adds to string", testSingleCharPlusEquOp));
	tests.addTest(Test("+= operator concatenates strings", testStringPlusEquOp));
	tests.addTest(Test("[] operator access works for reading", testSquareBracketOpRead));
	tests.addTest(Test("[] operator access works for writing", testSquareBracketOpWrite));
	tests.addTest(Test("[] operator access throws when it should", testSquareBracketOpThrow));
	tests.addTest(Test("[] operator is also const compatible", testConstSquareBracketOp));
	tests.addTest(Test("push_back() method works", testPushBack));
	tests.addTest(Test("pop_back() should return", testPopBack));
	tests.addTest(Test("pop_back() should throw exception when empty", testPopBackThrow));
	tests.addTest(Test("character insert should add a character", testInsertChar));
	tests.addTest(Test("insert char* string should add the string", testInsertCharString));
	tests.addTest(Test("insert String class string should add the string", testInsertString));
	tests.addTest(Test("insert should throw if index is invalid", testInsertThrows));
	tests.addTest(Test("erase should remove characters", testErase));
	tests.addTest(Test("erase should throw exception if arguments are invalid", testEraseThrows));
	tests.addTest(Test("swap should swap strings", testSwap));
	tests.addTest(Test("to_C_string should return a valid size() string", testCString));
	tests.addTest(Test("<< operator writes the string to stream", testStreamOutput));
	tests.addTest(Test(">> operator reads a string from stream", testStreamInput));
	tests.addTest(Test("iterators gonna iterate, rate, rate", testIterators));
	tests.addTest(Test("iterators throws", testIteratorsThrow));

	tests.runAll();
	tests.summary();
	tests.details();
}
