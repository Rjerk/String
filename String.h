#ifndef STRING_H
#define STRING_H

#include <utility>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <cstddef>

using std::cout;
using std::cin;
using std::endl;

using size_type = std::uint32_t;
using iterator = char *;

class String {
	// Non-member functions
	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(const char* lhs, const String& rhs);
	friend String operator+(const String& lhs, const char* rhs);
	friend String operator+(char lhs, const String& rhs);
	friend String operator+(const String& lhs, char rhs);
	friend String operator+(String&& lhs, const String& rhs);
	friend String operator+(const String& lhs, String&& rhs);
	friend String operator+(String&& lhs, String&& rhs);
	friend String operator+(const char* lhs, String&& rhs);
	friend String operator+(String&& lhs, const char* rhs);
	friend String operator+(String&& lhs, char rhs);
	friend String operator+(char lhs, String&& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator==(const char* lhs, const String& rhs);
	friend bool operator==(const String& lhs, const char* rhs);
	friend bool operator!=(const char* lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const char* rhs);
	friend bool operator<(const char* lhs, const String& rhs);
	friend bool operator<(const String& lhs, const char* rhs);
	friend bool operator<=(const char* lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const char* rhs);
	friend bool operator>(const char* lhs, const String& rhs);
	friend bool operator>(const String& lhs, const char* rhs);
	friend bool operator>=(const char* lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const char* rhs);
	friend void swap(String& lhs, String& rhs) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const String& rhs);
	friend std::istream& operator>>(std::istream& is, String& rhs);
	friend String to_string(int value);
	friend String to_string(long value);
	friend String to_string(long long value);
	friend String to_string(unsigned value);
	friend String to_string(unsigned long value);
	friend String to_string(unsigned long long value);
	friend String to_string(float value);
	friend String to_string(double value);
	friend String to_string(long double value);
public:
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

// Constructor
String::String():
	data_(NULL), size_(0), capacity_(0)
{
}

String::String(const String& rhs):
	size_(rhs.size()), capacity_(rhs.capacity()), data_(new char[capacity_])
{
	memcpy(data_, rhs.data_, size_);
}

String::String(String&& rhs):
	size_(rhs.size()), capacity_(rhs.capacity()), data_(rhs.data_)
{
	rhs.data_ = nullptr;
}

String::String(const String& rhs, size_type pos, size_type count)
{
	if(pos >= rhs.size())
		throw std::out_of_range("String::String");
	size_ = (count + pos > rhs.size() ? (rhs.length()-pos) : count);
	capacity_ = size_;
	data_ = new char[capacity_];
	strncpy(data_, rhs.data_+pos, size_);
}

String::String(const String& rhs, size_type pos):
	String(rhs, pos, rhs.size()) // delegating constructor
{
}

String::String(const char* s):
	size_(strlen(s)), capacity_(size_), data_(new char[capacity_])
{
	strcpy(data_, s);
}

String::String(const char* s, size_type count)
{
	if (count > strlen(s))
		throw std::out_of_range("String::String");
	size_ = count;
	capacity_ = size_;
	data_ = new char[capacity_];
	memcpy(data_, s, capacity_);
}

String::String(size_type count, char ch):
	size_(count), capacity_(size_), data_(new char[capacity_])
{
	memset(data_, ch, capacity_);
}

String::String(iterator first, iterator last):
	size_(last-first), capacity_(size_), data_(new char[capacity_])
{
	memcpy(data_, first, capacity_);
}

String::String(std::initializer_list<char> init):
	size_(init.size()), capacity_(size_), data_(new char[capacity_])
{
	size_type i = 0;
	for (auto c : init)
		data_[i++] = c;
}

// Destructor
String::~String() noexcept
{
	delete [] data_;
}

String& String::operator=(String rhs)
{
	this->swap(rhs);
	return *this;
}

String& String::operator=(const char* s)
{
	if (capacity_ < strlen(s))
		reallocate(strlen(s));
	memset(data_, char(), size_);
	memcpy(data_, s, strlen(s));
	return *this;
}

String& String::operator=(char ch)
{
	if (capacity_ > 0) {
		this->clear();
	} else {
		data_ = new char(1);
		capacity_ = 1;
	}
	data_[0] = ch;
	size_ = 1;
	return *this;
}

String& String::operator=(std::initializer_list<char> ilist)
{
	if (capacity_ < ilist.size())
		reallocate(ilist.size());
	memset(data_, char(), size_);
	size_type j = 0;
	for (auto i : ilist)
		data_[j++] = i;
	return *this;
}

// assign
String& String::assign(size_type count, char ch)
{
	if (count > maxsize_)
		throw std::length_error("String::assign");
	if (count > capacity_)
		reallocate(count);
	memset(data_, ch, count);
	return *this;
}

String& String::assign(const String& str)
{
	return this->assign(str, 0, str.size());
}

String& String::assign(const String& str, size_type pos, size_type count)
{
	if (pos > str.size())
		throw std::out_of_range("String::assign");
	if (pos + count > maxsize_)
		throw std::length_error("String::assign");
	count = (pos + count > str.size() ? (str.size() - pos) : count);
	if (count > size_)
		reallocate(count);
	memcpy(data_, str.data_+pos, count);
	return *this;
}

String& String::assign(String&& str) noexcept
{
	this->swap(str);
	str.data_ = nullptr;
	return *this;
}

String& String::assign(const char* s, size_type count)
{
	count = (count > strlen(s) ? strlen(s) : count);
	if (count > capacity_)
		reallocate(count);
	memcpy(data_, s, count);
	return *this;
}

String& String::assign(const char* s)
{
	return this->assign(s, strlen(s));
}

// Iterators
iterator String::begin() noexcept
{
	return data_;
}

iterator String::end() noexcept
{
	return data_ + size_;
}

// Capacity
void String::reserve(size_type new_cap)
{
	if (new_cap > maxsize_)
		throw std::length_error("String::reserve");
	if (new_cap <= capacity_ || new_cap <= size_)
		return ;
	char* tmp = new char[size_];
	memcpy(tmp, data_, size_);
	delete [] data_;
	data_ = tmp;
	tmp = nullptr;
	capacity_ *= 2; // if new_cap > capacity_, capacity *= 2.
}

void String::shrink_to_fit()
{
	if (size_ < capacity_)
		reallocate(size_);
}

// Operation
void String::clear()
{
	memset(data_, char(), size_);
	size_ = 0;
}

String& String::insert(size_type index, size_type count, char ch)
{
	if (index > size_)
		throw std::out_of_range("String::insert");
	if (size_+count > maxsize_)
		throw std::length_error("String::insert");
	size_type pos = size_-1;
	size_ = size_ + count;
	if (size_ > capacity_)
		reallocate(size_);
	
	for (size_type i = size_ - 1; pos >= index;)
		data_[i--] = data_[pos--];
	for (size_type i = 0; i < count; ++i)
		data_[index++] = ch;
	return *this;
}

String& String::insert(size_type index, const char* s)
{
	return this->insert(index, s, strlen(s));
}

String& String::insert(size_type index, const char* s, size_type count) //
{
	if (index > this->size())
		throw std::out_of_range("String::insert");
	//
}

String& String::insert(size_type index, const String& str)
{
	return this->insert(index, str, 0, str.size());
}

String& String::insert(size_type index, const String& str, size_type index_str, size_type count) //
{
	if (index > this->size())
		throw std::out_of_range("String::insert");
	//
}

iterator String::insert(iterator pos, char ch)
{
	
}

void String::insert(iterator pos, size_type count, char ch)
{
	
}

String& String::erase(size_type index, size_type count)
{
	if (index > this->size())
		throw std::out_of_range("String::erase");
	if (count > size_) count = size_;
	count = std::min(count, size_-index);
	if (index + count < size_) {
		for (size_type i = index+count; i < size_; ++i)
			data_[i-count] = data_[i];
		size_ -= count;
	} else {
		size_ = index;
		memset(data_+size_, char(), count);
	}
	return *this;
}

iterator String::erase(iterator pos)
{
	return this->erase(pos, pos+1);
}

iterator String::erase(iterator first, iterator last)
{
	iterator fst = first, lst = last;
	while (fst < last && lst < this->end())
		*fst++ = *lst++;
	while (lst != this->end())
		*fst++ = *lst++;
	memset(fst, char(), this->end()-fst);
	size_ -= (last-first);
	return first;
}

void String::push_back(char ch)
{
	if (size_+1 > maxsize_)
		throw std::length_error("String::push_back");
	++size_;
	if (size_ > capacity_)
		reallocate(size_);
	data_[size_] = ch;
}

void String::pop_back()
{
	erase(size()-1, 1);
}

String& String::append(size_type count, char ch)
{
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type pos = size_;
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	while (count--) {
		data_[pos++] = ch;
	}
	return *this;
}

String& String::append(const String& str)
{
	return this->append(str, 0, str.size());
}

String& String::append(const String& str, size_type pos, size_type count)
{
	if (pos > str.size())
		throw std::out_of_range("String::append");
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type sz = size_;
	count = (pos + count > str.size() ? (str.size() - pos) : count);
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	for (int i = 0; i < count; ++i)
		data_[sz++] = str.data_[pos++];
	return *this;
}

String& String::append(const char* s, size_type count)
{
	if (size_ + count > maxsize_)
		throw std::length_error("String::append");
	size_type sz = size_;
	size_ += count;
	if (size_ > capacity_)
		reallocate(size_);
	memcpy(data_+sz, s, count);
	return *this;
}

String& String::append(const char* s)
{
	return this->append(s, strlen(s));
}

String& String::operator+=(const String& rhs)
{
	return this->append(rhs);
}

String& String::operator+=(char c)
{
	return this->append(1, c);
}

String& String::operator+=(const char* s)
{
	return this->append(s);
}

String& String::operator+=(std::initializer_list<char> ilist)
{
	String tmp(ilist);
	return this->append(tmp);
}

int String::compare(const String& rhs) const noexcept
{
	if (this == &rhs) return 0;
	if (size_ < rhs.size())
		return -1;
	else if (size_ > rhs.size())
		return 1;
	else {
		for (size_type i = 0; i < size_; ++i) {
			if (rhs.data_[i] > data_[i])
				return -1;
			else if (rhs.data_[i] < data_[i])
				return 1;
		}
		return 0;
	}
}

int String::compare(size_type pos1, size_type count1, const String& str) const
{
	return this->compare(pos1, count1, str, 0, str.size());
}

int String::compare(size_type pos1, size_type count1, const String& str, size_type pos2, size_type count2) const
{
	return (this->substr(pos1, count1)).compare(str.substr(pos2, count2));
}

int String::compare(const char* s) const
{
	if (size_ < strlen(s))
		return -1;
	else if (size_ > strlen(s))
		return 1;
	else {
		for (size_type i = 0; i < size_; ++i) {
			if (s[i] > data_[i])
				return -1;
			else if (s[i] < data_[i])
				return 1;
		}
		return 0;
	}
}

int String::compare(size_type pos1, size_type count1, const char* s) const
{
	return this->compare(pos1, count1, s, strlen(s));
}

int String::compare(size_type pos1, size_type count1, const char* s, size_type count2) const
{
	if (pos1 > this->size()) 
		throw std::out_of_range("String::compare");
	String tmp(s, count2);
	return this->substr(pos1, count1).compare(tmp);
}

String& String::replace(size_type pos, size_type count, const String& str)
{
	return this->replace(pos, count, str, 0, str.size());
}

String& String::replace(size_type pos1, size_type count1, const String& str, size_type pos2, size_type count2)
{
	if (pos1 > this->size() || pos2 > str.size())
		throw std::out_of_range("String::replace");
	return this->erase(pos1, count1).insert(pos1, str, pos2, count2);
}

String& String::replace(size_type pos1, size_type count1, const char* cstr, size_type count2)
{
	if (pos1 > this->size())
		throw std::out_of_range("String::replace");
	return this->erase(pos1, count1).insert(pos1, cstr, count2);
}

String& String::replace(size_type pos, size_type count, const char* cstr)
{
	return this->replace(pos, count, cstr, strlen(cstr));
}

String& String::replace(size_type pos1, size_type count1, size_type count2, char ch)
{
	if (pos1 > this->size())
		throw std::out_of_range("String::replace");
	return this->erase(pos1, count1).insert(pos1, count2, ch);
}

String String::substr(size_type pos, size_type count) const
{
	if (pos > this->size())
		throw std::out_of_range("String::substr");
	if (count == npos || (pos + count > size_))
		count = size_ - pos;
	return String(*this, pos, count);
}

size_type String::copy(char* dest, size_type count, size_type pos) const
{
	if (pos > this->size())
		throw std::out_of_range("String::copy");
	count = ((pos + count) > size_ ? (size_ - pos) : count);
	memcpy(dest, data_+pos, count);
	return count;
}

void String::resize(size_type count)
{
	if (count > maxsize_)
		throw std::length_error("String::resize(size_type count)");
	resize(count, char());
}

void String::resize(size_type count, char ch)
{
	if (count > maxsize_)
		throw std::length_error("String::resize(size_type count, char ch)");
	if (count == size_) {
		return ;
	} else {
		char* tmp = new char[count];
		if (count < size_) {
			memcpy(tmp, data_, count);
			delete [] data_;
		} else {
			memcpy(tmp, data_, size_);
			delete [] data_;
			for (size_type i = size_; i < count; ++i)
				tmp[i] = ch;
			if (count > capacity_) capacity_ *= 2; // if count > capacity_, capacity_ *= 2.
		}
		size_ = count;
		data_ = tmp;
		tmp = nullptr;
	}
}

void String::swap(String& rhs) noexcept
{
	using std::swap;
	swap(data_, rhs.data_);
	swap(size_, rhs.size_);
	swap(capacity_, rhs.capacity_);
}

size_type String::find(const String& str, size_type pos) const
{
	return this->find(str.data(), pos, str.size());
}

size_type String::find(const char* s, size_type pos, size_type count) const
{
	if (pos < size_) {
		for (size_type i = pos; i+count <= this->size(); ++i) {
			if (this->compare(i, count, s, count) == 0)
				return i;
		}
	}
	return npos;
}

size_type String::find(const char* s, size_type pos) const
{
	return this->find(s, pos, strlen(s));
}

size_type String::find(char ch, size_type pos) const
{
	if (pos < this->size()) {
		for (size_type i = pos; i < this->size(); ++i)
			if (data_[i] == ch)
				return i;
	}
	return npos;
}

size_type String::rfind(const String& str, size_type pos) const
{
	return this->rfind(str.data(), pos, str.size());
}

size_type String::rfind(const char* s, size_type pos, size_type count) const
{
	if (size_ > 0) {
		if (pos >= size_) pos = size_ - 1;
		if (count > size_) count = size_;
		for (size_type i = pos-count+1; i >= 0; --i) {
			if (this->compare(i, count, s, count) == 0)
				return i;
		}
	}
	return npos;
}

size_type String::rfind(const char* s, size_type pos) const
{
	return this->rfind(s, pos, strlen(s));
}

size_type String::rfind(char ch, size_type pos) const
{
	if (size_ > 0) {
		if (pos >= size_) pos = size_ - 1;
		for (size_type i = pos; i >= 0; --i) {
			if (data_[i] == ch)
				return i;
		}
	}
	return npos;
}

size_type String::find_first_of(const String& str, size_type pos) const
{
	return this->find_first_of(str.data(), pos, str.size());
}

size_type String::find_first_of(const char* s, size_type pos, size_type count) const
{
	if (pos < size_) {
		if (count > strlen(s)) count = strlen(s);
		for (size_type i = pos; i < size_; ++i) {
			for (size_type j = 0; j < count; ++j) {
				if (data_[i] == s[j])
					return i;
			}
		} 
	}
	return npos;
}

size_type String::find_first_of(const char* s, size_type pos) const
{
	return this->find_first_of(s, pos, strlen(s));
}

size_type String::find_first_of(char ch, size_type pos) const
{
	return this->find(ch, pos);
}

size_type String::find_first_not_of(const String& str, size_type pos) const
{
	return this->find_first_not_of(str.data(), pos, str.size());
}

size_type String::find_first_not_of(const char* s, size_type pos, size_type count) const
{
	if (pos < size_) {
		if (count > strlen(s)) count = strlen(s);
		for (size_type i = pos; i < size_; ++i) {
			bool found = false;
			for (size_type j = 0; j < count; ++j) {
				if (data_[i] == s[j]) {
					found = true;
					break;
				}
			}
			if (found == false)
				return i;
		}
	}
	return npos;
}

size_type String::find_first_not_of(const char* s, size_type pos) const
{
	return this->find_first_not_of(s, pos, strlen(s));
}

size_type String::find_first_not_of(char ch, size_type pos) const
{
	if (pos < this->size()) {
		for (size_type i = pos; i < this->size(); ++i)
			if (data_[i] != ch)
				return i;
	}
	return npos;
}

size_type String::find_last_of(const String& str, size_type pos) const
{
	return this->find_last_of(str.data(), pos, str.size());
}

size_type String::find_last_of(const char* s, size_type pos, size_type count) const
{
	if (size_ > 0) { // 5 3
		if (pos >= size_) pos = size_ - 1;
		if (count > size_) count = size_;
		for (size_type i = pos; i >= 0; --i) {
			for (size_type j = 0; j < count; ++j) {
				if (data_[i] == s[j])
					return i;
			}
		}
	}
	return npos;
}

size_type String::find_last_of(const char* s, size_type pos) const
{
	return this->find_last_of(s, pos, strlen(s));
}

size_type String::find_last_of(char ch, size_type pos) const
{
	return this->rfind(ch, pos);
}

size_type String::find_last_not_of(const String& str, size_type pos) const
{
	return this->find_last_not_of(str.data(), pos, str.size());
}

size_type String::find_last_not_of(const char* s, size_type pos, size_type count) const
{
	if (size_ > 0) {
		if (pos > size_) pos = size_ - 1;
		if (count > strlen(s)) count = strlen(s);
		
		for (size_type i = pos; i >= 0; --i) {
			bool found = false;
			for (size_type j = 0; j < count; ++j) {
				if (data_[i] == s[j]) {
					found = true;
					break;
				}
			}
			if (found == false)
				return i;
		}
	}
	return npos;
}

size_type String::find_last_not_of(const char* s, size_type pos) const
{
	return this->find_last_not_of(s, pos, strlen(s));
}

size_type String::find_last_not_of(char ch, size_type pos) const
{
	if (size_ > 0) {
		if (pos > size_)
		pos = size_ - 1;
		for (size_type i = pos; i >=0; --i) {
			if (data_[i] != ch)
				return i;
		}
	}
	return npos;
}

// helper: reallocate the memory.
void String::reallocate(size_type size)
{
	if (size * 2 > maxsize_) 
		throw std::length_error("String::expand(size_type size)");
	size_type original_sz = size_;
	size_ = size;
	if (size_ > capacity_ && size_ < 2*capacity_ && capacity_ != 0)
		capacity_ *= 2;
	else
		capacity_ = size;
	char* tmp = new char[capacity_];
	memcpy(tmp, data_, original_sz);
	delete [] data_;
	data_ = tmp;
	tmp = nullptr;
}

// Non-member functions
String operator+(const String& lhs, const String& rhs)
{
	return String(lhs).append(rhs);
}

String operator+(const char* lhs, const String& rhs)
{
	return String(lhs).append(rhs);
}

String operator+(const String& lhs, const char* rhs)
{
	return String(lhs).append(rhs);
}

String operator+(char lhs, const String& rhs)
{
	return String(1, lhs).append(rhs);
}

String operator+(const String& lhs, char rhs)
{
	return String(lhs).append(1, rhs);
}

String operator+(String&& lhs, const String& rhs)
{
	return lhs.append(rhs);
}

String operator+(const String& lhs, String&& rhs)
{
	return String(lhs).append(rhs);
}

String operator+(String&& lhs, String&& rhs)
{
	return lhs.append(rhs);
}

String operator+(const char* lhs, String&& rhs)
{
	return String(lhs).append(rhs);
}

String operator+(String&& lhs, const char* rhs)
{
	return lhs.append(rhs);
}

String operator+(String&& lhs, char rhs)
{
	return lhs.append(1, rhs);
}

String operator+(char lhs, String&& rhs)
{
	return String(1, lhs).append(rhs);
}

bool operator==(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) != 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) > 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) >= 0;
}

bool operator==(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) == 0;
}

bool operator==(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) == 0;
}

bool operator!=(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) != 0;
}

bool operator!=(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) != 0;
}

bool operator<(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) >= 0;
}

bool operator<(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) < 0;
}

bool operator<=(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) > 0;
}

bool operator<=(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) <= 0;
}

bool operator>(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) <= 0;
}

bool operator>(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) > 0;
}

bool operator>=(const char* lhs, const String& rhs)
{
	return rhs.compare(lhs) < 0;
}

bool operator>=(const String& lhs, const char* rhs)
{
	return lhs.compare(rhs) >= 0;
}

void swap(String& lhs, String& rhs) noexcept
{
	lhs.swap(rhs);
}

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
		os << rhs.data_[i];
	return os;
}

std::istream& operator>>(std::istream& is, String& rhs)
{
	char tmp[1000];
	is >> tmp;
	rhs = tmp;
	return is;
}

String to_string(int value)
{
	char buf[100];
	std::sprintf(buf, "%d", value);
	return String(buf);
}

String to_string(long value)
{
	char buf[100];
	std::sprintf(buf, "%ld", value);
	return String(buf);
}

String to_string(long long value)
{
	char buf[100];
	std::sprintf(buf, "%lld", value);
	return String(buf);
}

String to_string(unsigned value)
{
	char buf[100];
	std::sprintf(buf, "%u", value);
	return String(buf);
}

String to_string(unsigned long value)
{
	char buf[100];
	std::sprintf(buf, "%lu", value);
	return String(buf);
}

String to_string(unsigned long long value)
{
	char buf[100];
	std::sprintf(buf, "%llu", value);
	return String(buf);
}

String to_string(float value)
{
	char buf[100];
	std::sprintf(buf, "%f", value);
	return String(buf);
}

String to_string(double value)
{
	char buf[100];
	std::sprintf(buf, "%f", value);
	return String(buf);
}

String to_string(long double value)
{
	char buf[100];
	std::sprintf(buf, "%lf", value);
	return String(buf);
}

#endif
