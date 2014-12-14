#include "string.h"
#include <stdexcept>
#include <cassert>

//private functions
void String::reset() {
	length_ = 0;
	size_ = 0;
	if (content_ != NULL) {
		delete [] content_;
	}
}

bool String::check() {
	//stored string must fit the buffer and if buffer size is 0, content_ must be NULL
	return (length_ <= size_) && !(size_ == 0 && content_ != NULL); 
}

//reallocate more memory
void String::resize(size_t new_size) {
	if (size_ >= new_size) return;
	assert(new_size >= length_);

	char* new_content = new char[new_size];

	if (content_ != NULL) {
		memcopy(content_, new_content, length_);
		delete [] content_;
	}
	content_ = new_content;
	size_ = new_size;
}

//helper functions
void memcopy(char* src, char* dst, size_t len) {
	if (len == 0) return;
	//avoid overlapping problems
	if (src == dst) return;
	if (src < dst) {
		size_t i = len;
		do {
			i--;
			dst[i] = src[i];
		} while(i > 0);
	} else {
		for(size_t i = 0; i < len; i++) {
			dst[i] = src[i];
		}
	}
}

//constructors
String::String(size_t size): length_(0), size_(size) {
	content_ = new char[size];
}

//string literal constructor
String::String(char* literal) {
	for(length_ = 0; literal[length_]; length_++);
	size_ = length_;
	content_ = new char[length_];

	for(size_t i = 0; i < length_; i++) {
		content_[i] = literal[i];
	}

	assert(check());
}

//default zero-arg constructor
String::String(): length_(0), content_(NULL), size_(0) {}

//copy constructor
String::String(String const& a): length_(a.length_), size_(a.length_) {
	content_ = new char[length_];
	memcopy(a.content_, content_, length_);
	assert(check());
}

//move constructor
String::String(String&& a): length_(a.length_), size_(a.size_), content_(a.content_) {
	a.content_ = NULL;
	a.reset();
}

//destructor
String::~String() {
	if (content_ != NULL) {
		delete [] content_;
	}
}

//copy assignment
String& String::operator=(String const& a) {
	length_ = a.length_;
	size_ = a.size_;
	content_ = new char[size_];
	assert(check());
	return *this;
}

//move assignment
String String::operator=(String &a) {
	length_ = a.length_;
	size_ = a.size_;
	content_ = content_;
	assert(check());
	return *this;
}

//accessors
size_t String::size() const {
	return length_;
}

//operators
String operator+(String const& a, String const& b) {
	size_t new_len = a.length_ + b.length_;
	char* new_content = new char[new_len];

	String new_string;
	new_string.size_ = new_len;
	new_string.length_ = new_len;
	new_string.content_ = new_content;

	for(size_t i = 0; i < a.length_; i++) {
		new_content[i] = a.content_[i];
	}

	for(size_t i = 0; i < b.length_; i++) {
		new_content[i + a.length_] = b.content_[i];
	}

	assert(new_string.check());
	return new_string;
}

String& String::operator+=(char const& a) {
	length_++;
	resize(length_);
	content_[length_ - 1] = a;

	assert(check());
	return *this;
}	

String& String::operator+=(String const& a) {
	size_t oldlen = length_;
	length_ += a.length_;
	resize(length_);
	memcopy(a.content_, content_ + oldlen, a.length_);

	assert(check());
	return *this;
}

char& String::operator[](size_t position) {
	if (position >= length_) {
		throw std::out_of_range("out of bounds []-operator call");
	}

	return content_[position];
}

//const version of []-operator
char String::operator[](size_t position) const {
	if (position >= length_) {
		throw std::out_of_range("out of bounds []-operator call");
	}

	return content_[position];
}

//stream operators
std::ostream& operator<<(std::ostream& out, String const& a) {
	for(size_t i = 0; i < a.length_; i++) {
		out << a.content_[i];
	}
	return out;
}

std::istream& operator>>(std::istream& in, String &a) {
	char temp;
	size_t length = 0;

	a.reset();

	//will read until EOF or error
	while(in >> temp) {
		length++;
		a += temp;
	}

	return in;
}

//iterator functions
String::iterator String::begin() {
	return String::iterator(*this, 0);
}

String::iterator String::end() {
	return String::iterator(*this, length_);
}

//container functions
void String::push_back(char c) {
	*this += c;
}

char String::pop_back() {
	if(length_ == 0) {
		throw std::out_of_range("pop_back() called for an empty string");
	}

	char ret = content_[length_ - 1];
	length_--;

	assert(check());
	return ret;
}

void String::insert(size_t index, char c) {
	if (index > length_) {
		throw new std::out_of_range("index out of bounds");
	}
	resize(length_ + 1);
	memcopy(content_ + index, content_ + index + 1, length_ - index);
	content_[index] = c;
	length_++;
	assert(check());
}

void String::insert(size_t index, char* str) {
	if (index > length_) {
		throw new std::out_of_range("index out of bounds");
	}
	size_t len = 0;
	while (str[len]) {
		len++;
	}

	resize(length_ + len);
	memcopy(content_ + index, content_ + index + len, length_ - index);
	memcopy(str, content_ + index, len);

	length_ += len;
	assert(check());
}

void String::insert(size_t index, String const& str) {
	if (index > length_) {
		throw new std::out_of_range("index out of bounds");
	}
	resize(length_ + str.length_);
	memcopy(content_ + index, content_ + index + str.length_, length_ - index);
	memcopy(str.content_, content_ + index, str.length_);

	length_ += str.length_;
	assert(check());
}

void String::erase(size_t from, size_t to) {
	if(from >= length_ || to >= length_ || to < from) {
		throw std::out_of_range("invalid parameters to erase(from, to)");
	}

	size_t len = to - from + 1;
	memcopy(content_ + to + 1, content_ + from, length_ - to - 1);
	length_ -= len;
	assert(check());
}

void String::swap(String& a) {
	size_t tmp_size = a.size_;
	size_t tmp_len = a.length_;
	char* tmp_content = a.content_;

	a.size_ = size_;
	a.length_ = length_;
	a.content_ = content_;

	size_ = tmp_size;
	length_ = tmp_len;
	content_ = tmp_content;
}

//iterator internals

String::iterator::iterator(String& string, size_t position): string_(string), pos_(position) {}

bool String::iterator::check() {
	return (pos_ <= string_.length_ && pos_ >= 0);
}

char String::iterator::operator*() {
	if (pos_ < string_.length_) {
		return string_.content_[pos_];
	}

	throw std::runtime_error("referenced invalid iterator");
}

String::iterator& String::iterator::operator++() {
	if (pos_ >= string_.length_) {
		throw std::out_of_range("overiterated");
	}

	pos_++;
	assert(check());
	return *this;
}

String::iterator String::iterator::operator++(int) {
	String::iterator tmp = *this;
	++*this;
	return tmp;
}

String::iterator& String::iterator::operator--() {
	if (pos_ == 0) {
		throw std::out_of_range("under iteration!");
	}
	pos_--;

	return *this;
}

String::iterator String::iterator::operator--(int) {
	String::iterator tmp = *this;
	--*this;
	return tmp;
}

bool String::iterator::operator==(iterator const& a) {
	return (&a.string_ == &string_ && a.pos_ == pos_);
}

bool String::iterator::operator!=(iterator const& a) {
	return !(*this==a);
}
