#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <initializer_list>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iostream>
#include "iterator.h"

namespace mystl {

constexpr size_t VEC_MIN_SIZE = 4;

template <typename T, typename Allocator = std::allocator<T>>
class Vector : private Allocator {
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<Allocator>::pointer; // since C++11
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer; // since C++11
	using iterator = pointer; // RandomAccessIterator
	using const_iterator = const_pointer; // const RandomAccessIterator
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
private:
	iterator elements;
	iterator first_free;
	iterator end_of_storage;
private:
	void fillAndInitialize(size_type n, const T& value);
	typename Allocator::pointer allocateAndFill(size_type n, const T& value);
	void doDestroy(iterator beg, iterator end);
	void doDeallocate();
	void moveToNewChunk(size_type new_cap);
	void copyBackward(const_iterator first, const_iterator last, const_iterator pos);
	void checkAndExpand();
	void expandCapacity(size_type new_cap);
public:
	explicit Vector(const Allocator& alloc_ = Allocator()) noexcept;
	Vector(size_type count, const T& value, const Allocator& alloc_ = Allocator());
	explicit Vector(size_t count, const Allocator& alloc_= Allocator());

	Vector(const Vector<T, Allocator>& rhs);
	Vector(Vector<T, Allocator>&& rhs) noexcept;
	Vector(std::initializer_list<T> init, const Allocator& alloc_ = Allocator());
	~Vector();

	Vector& operator=(Vector other) noexcept;

	void assign(size_type count, const T& value);
	void assign(std::initializer_list<T> ilist);

	allocator_type get_allocator() const;

	reference at(size_type pos);
	const_reference at(size_type pos) const;

	reference operator[](size_type pos);
	const_reference operator[](size_type pos) const;

	reference front();
	const_reference front() const;

	reference back();
	const_reference back() const;

	pointer data() noexcept;
	const_pointer data() const noexcept;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;

	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;
	const_reverse_iterator crend() const noexcept;

	bool empty() const noexcept;
	size_type size() const noexcept;
	size_type max_size() const noexcept;
	size_type capacity() const noexcept;

	void reserve(size_type new_cap);
	void shrink_to_fit();
	void clear() noexcept;

	iterator insert(const_iterator pos, const T& value);
	iterator insert(const_iterator pos, T&& value);
	iterator insert(const_iterator pos, size_type count, const T& value);

	template <typename InputIt, typename = std::enable_if_t<has_iterator_deref<T>::value>>
	iterator insert(const_iterator pos, InputIt first, InputIt last);

	iterator insert(const_iterator pos, std::initializer_list<T> ilist);

	template <typename... Args>
	iterator emplace(const_iterator pos, Args&&... args);

	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);

	void push_back(const T& value);
	void push_back(T&& value);

	template <typename... Args>
	void emplace_back(Args&&... args);

	void pop_back();

	void resize(size_type count);
	void resize(size_type count, const value_type& value);

	void swap(Vector& rhs) noexcept;
};

template <typename T, typename Alloc>
void swap(Vector<T, Alloc>& lhs, Vector<T, Alloc>& rhs) noexcept;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v);

template <typename T, typename Alloc>
bool operator==(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

template <typename T, typename Alloc>
bool operator!=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

template <typename T, typename Alloc>
bool operator<(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

template <typename T, typename Alloc>
bool operator<=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

template <typename T, typename Alloc>
bool operator>(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

template <typename T, typename Alloc>
bool operator>=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs);

#include "Vector.inl"
}

#endif
