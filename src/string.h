#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <iostream>

class String {
	private:
		size_t length_; //number of stored characters
		char* content_; //pointer to dynamically allocated memory
		size_t size_;   //size of the memory

		void reset();
		bool check();
		void resize(size_t new_size);

	public:
		String();
		String(char* literal);
		explicit String(size_t size);
		String(String const& a);
		String(String&& a);
		~String();

		String& operator=(String const& a);
		String operator=(String &a);
		String& operator+=(char const& a);
		String& operator+=(String const& a);
		char& operator[](size_t position);
		char operator[](size_t position) const;

		size_t size() const;

		void push_back(char c);
		char pop_back();
		void insert(size_t index, char c);
		void insert(size_t index, char* str);
		void insert(size_t index, String const& str);
		void erase(size_t from, size_t to);
		void swap(String& a);
		char* to_C_string();

	friend String operator+(String const& a, String const& b);

	friend std::ostream& operator<<(std::ostream&, String const& a);
	friend std::istream& operator>>(std::istream&, String& a);
	
	class iterator {
		private:
			String& string_;
			size_t pos_;

			bool check();

		public:
			iterator(String& string, size_t position);
			char operator*();
			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);
			bool operator==(iterator const& a);
			bool operator!=(iterator const& a);
	};

	iterator begin();
	iterator end();
};

void memcopy(char* src, char* dst, size_t len);
//STRING_H
#endif
