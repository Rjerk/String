#ifndef STRING_H
#define STRING_H

#include <cstdint>
#include <initializer_list>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace mystl {

class String {
	friend std::ostream& operator<<(std::ostream& os, const String& rhs);
public:
	using size_type = std::uint32_t;
	using iterator = char *;
	// Constructor
	String();
	String(const String& other);
	String(String&& other);
	String(const String& other, size_type pos, size_type count);
	String(const String& other, size_type pos);
	String(const char* s);
	String(const char* s, size_type);
	String(size_type count, char ch);
	String(iterator first, iterator last);
	String(std::initializer_list<char> init);
	// Destructor
	~String() noexcept;
	String& operator=(String str);
	String& operator=(const char* s);
	String& operator=(char ch);
	String& operator=(std::initializer_list<char> ilist);
	// assign
	String& assign(size_type count, char ch);
	String& assign(const String& str);
	String& assign(const String& str, size_type pos, size_type count);
	String& assign(String&& str) noexcept;
	String& assign(const char* s, size_type count);
	String& assign(const char* s);
public:
	// Element access
	char& at(size_type pos) { if (pos > size()) throw std::out_of_range("String::at"); return data_[pos]; }
	const char& at(size_type pos) const { if (pos > size()) throw std::out_of_range("String::at"); return static_cast<const char&>(data_[pos]); }
	char& operator[](size_type pos) { return data_[pos]; }
	const char& operator[](size_type pos) const { return data_[pos]; }
	char front() { return data_[0]; }
	const char front() const { return data_[0]; }
	char back() { return data_[size_-1]; }
	const char back() const { return data_[size_-1]; }
	const char* data() const { return static_cast<const char*>(data_); }
	char* data() { return data_;}
	const char* c_str() const { data_[size_] = '\0'; return static_cast<const char*>(data_); }
	// Iterators
	iterator begin() noexcept;
	iterator end() noexcept;
	// Capacity
	bool empty() const { return size_ == 0; }
	size_type size() const { return size_; }
	size_type length() const { return size_; }
	size_type max_size() const { return maxsize_; }
	void reserve(size_type new_cap = 0);
	size_type capacity() const { return capacity_; }
	void shrink_to_fit();
	// Operations
	void clear();
	String& insert(size_type index, size_type count, char ch);
	String& insert(size_type index, const char* s);
	String& insert(size_type index, const char* s, size_type count);
	String& insert(size_type index, const String& str);
	String& insert(size_type index, const String& str, size_type index_str, size_type count);
	iterator insert(iterator pos, char ch);
	void insert(iterator pos, size_type count, char ch);
	String& erase(size_type index = 0, size_type count = npos);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	void push_back(char ch);
	void pop_back();
	String& append(size_type count, char ch);
	String& append(const String& str);
	String& append(const String& str, size_type pos, size_type count);
	String& append(const char* s, size_type count);
	String& append(const char* s);
	String& operator+=(const String& rhs);
	String& operator+=(char c);
	String& operator+=(const char* s);
	String& operator+=(std::initializer_list<char> ilist);
	int compare(const String& rhs) const noexcept;
	int compare(size_type pos1, size_type count1, const String& str) const;
	int compare(size_type pos1, size_type count1, const String& str, size_type pos2, size_type count2) const;
	int compare(const char* s) const;
	int compare(size_type pos1, size_type count1, const char* s) const;
	int compare(size_type pos1, size_type count1, const char* s, size_type count2) const;
	String& replace(size_type pos, size_type count, const String& str);
	String& replace(size_type pos1, size_type count1, const String& str, size_type pos2, size_type count2);
	String& replace(size_type pos1, size_type count1, const char* cstr, size_type count2);
	String& replace(size_type pos, size_type count, const char* cstr);
	String& replace(size_type pos1, size_type count1, size_type count2, char ch);
	String substr(size_type pos = 0, size_type count = npos) const;
	size_type copy(char* dest, size_type count, size_type pos = 0) const;
	void resize(size_type count);
	void resize(size_type count, char ch);
	void swap(String& rhs) noexcept;
	// Search
	size_type find(const String& str, size_type pos = 0) const;
	size_type find(const char* s, size_type pos, size_type count) const;
	size_type find(const char* s, size_type pos = 0) const;
	size_type find(char ch, size_type pos = 0) const;
	size_type rfind(const String& str, size_type pos = npos) const;
	size_type rfind(const char* s, size_type pos, size_type count) const;
	size_type rfind(const char* s, size_type pos = npos) const;
	size_type rfind(char ch, size_type pos = npos) const;
	size_type find_first_of(const String& str, size_type pos = 0) const;
	size_type find_first_of(const char* s, size_type pos, size_type count) const;
	size_type find_first_of(const char* s, size_type pos = 0) const;
	size_type find_first_of(char ch, size_type pos = 0) const;
	size_type find_first_not_of(const String& str, size_type pos = 0) const;
	size_type find_first_not_of(const char* s, size_type pos, size_type count) const;
	size_type find_first_not_of(const char* s, size_type pos = 0) const;
	size_type find_first_not_of(char ch, size_type pos = 0) const;
	size_type find_last_of(const String& str, size_type pos = npos) const;
	size_type find_last_of(const char* s, size_type pos, size_type count) const;
	size_type find_last_of(const char* s, size_type pos = npos) const;
	size_type find_last_of(char ch, size_type pos = npos) const;
	size_type find_last_not_of(const String& str, size_type pos = npos) const;
	size_type find_last_not_of(const char* s, size_type pos, size_type count) const;
	size_type find_last_not_of(const char* s, size_type pos = npos) const;
	size_type find_last_not_of(char ch, size_type pos = npos) const;
public:
	// Constants
	static const size_type npos = -1;
private:
	void reallocate(size_type size);
private:
	size_type size_;
	size_type capacity_;
	char* data_;
	static const size_type maxsize_ = static_cast<size_type>(-1) / sizeof(char) - 1;
};

String operator+(const String& lhs, const String& rhs);
String operator+(const char* lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(char lhs, const String& rhs);
String operator+(const String& lhs, char rhs);
String operator+(String&& lhs, const String& rhs);
String operator+(const String& lhs, String&& rhs);
String operator+(String&& lhs, String&& rhs);
String operator+(const char* lhs, String&& rhs);
String operator+(String&& lhs, const char* rhs);
String operator+(String&& lhs, char rhs);
String operator+(char lhs, String&& rhs);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator==(const char* lhs, const String& rhs);
bool operator==(const String& lhs, const char* rhs);
bool operator!=(const char* lhs, const String& rhs);
bool operator!=(const String& lhs, const char* rhs);
bool operator<(const char* lhs, const String& rhs);
bool operator<(const String& lhs, const char* rhs);
bool operator<=(const char* lhs, const String& rhs);
bool operator<=(const String& lhs, const char* rhs);
bool operator>(const char* lhs, const String& rhs);
bool operator>(const String& lhs, const char* rhs);
bool operator>=(const char* lhs, const String& rhs);
bool operator>=(const String& lhs, const char* rhs);

void swap(String& lhs, String& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const String& rhs);
std::istream& operator>>(std::istream& is, String& rhs);

String to_string(int value);
String to_string(long value);
String to_string(long long value);
String to_string(unsigned value);
String to_string(unsigned long value);
String to_string(unsigned long long value);
String to_string(float value);
String to_string(double value);
String to_string(long double value);

#include "String.inl"
}

#endif
