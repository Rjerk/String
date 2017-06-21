#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <initializer_list> // initializer_list
#include <memory> // unique_ptr
#include <iterator>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

namespace mystl {

const size_t VEC_MIN_SIZE = 4;

template <typename T, typename Allocator = std::allocator<T>>
class Vector : private Allocator {
public:
	template <typename Type, typename Alloc>
	friend void swap(Vector<Type, Alloc>& lhs, Vector<Type, Alloc>& rhs) noexcept;
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
protected:
	iterator elements;
	iterator first_free;
	iterator end_of_storage;
	void fillAndInitialize(size_type n, const T& value)
	{
		elements = allocateAndFill(n, value);
		first_free = elements + n;
		end_of_storage = first_free;
	}
	typename Allocator::pointer allocateAndFill(size_type n, const T& value)
	{
		auto result = Allocator::allocate(n);
		std::uninitialized_fill_n(result, n, value);
		return result;
	}
	void doDestroy(iterator beg, iterator end)
	{
		if (beg != end) {
			for ( ; beg != end ; ++beg)
				Allocator::destroy(beg);
		}
	}
	void doDeallocate()
	{
		if (elements)
			Allocator::deallocate(elements, end_of_storage-elements);
	}
	void moveToNewChunk(size_type new_cap)
	{
		T* new_data = Allocator::allocate(new_cap);
		T* new_first_free = std::uninitialized_copy(elements, first_free, new_data);
		doDestroy(elements, first_free);
		doDeallocate();
		elements = new_data;
		first_free = new_first_free;
		end_of_storage = elements + new_cap;
	}
	void copyBackward(const_iterator first, const_iterator last, const_iterator pos)
	{
		for ( ; last >= first; --last)
			Allocator::construct(pos--, *last);
	}
//	template <typename... Args>
//	void doInsert(const_iterator pos, Args&&... args)
//	{
//		if (first_free < end_of_storage) {
//			auto val = value_type(std::forward<Args>(args)...);
//
//
//
//		} else if (first_free == end_of_storage) {
//
//		}
//	}
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

	//iterator insert(const_iterator pos, T value);
	iterator insert(iterator pos, const T& value);
	// iterator insert(const_iterator pos, T&& value);
	iterator insert(iterator pos, size_type count, const T& value);
	iterator insert(iterator pos, std::initializer_list<T> ilist);

	template <typename... Args>
	iterator emplace(iterator pos, Args&&... args);

	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);

	void push_back(const T& value);
	void push_back(T&& value);

	template <typename... Args>
	void emplace_back(Args&&...args);

	void pop_back();

	void resize(size_type count);
	void resize(size_type count, const value_type& value);

	void swap(Vector& rhs) noexcept;
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator& alloc_) noexcept
	: elements(nullptr), first_free(nullptr), end_of_storage(nullptr)
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_type count, const T& value, const Allocator& alloc_)
	: Allocator(alloc_)
{
	fillAndInitialize(count, value);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const Allocator& alloc_)
	: Vector(count, T(), alloc_)
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector<T, Allocator>& rhs)
{
	elements = Allocator::allocate(rhs.end_of_storage-rhs.elements);
	first_free = std::uninitialized_copy(rhs.elements, rhs.first_free, elements);
	end_of_storage = rhs.end_of_storage;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector<T, Allocator>&& rhs) noexcept
	: elements(nullptr), first_free(nullptr), end_of_storage(nullptr)
{
	this->swap(rhs);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init, const Allocator& alloc_)
	: Allocator(alloc_)
{
	elements = Allocator::allocate(init.size());
	std::uninitialized_copy_n(init.begin(), init.size(), elements);
	first_free = elements + init.size();
	end_of_storage = first_free;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
	if (capacity() != 0) {
		doDestroy(elements, first_free);
		doDeallocate();
		elements = first_free = end_of_storage = nullptr;
	}
}

template <typename T, typename Allocator>
Vector<T, Allocator>&
Vector<T, Allocator>::operator=(Vector rhs) noexcept
{
	this->swap(rhs);
	return *this;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::assign(size_type count, const T& value)
{
	if (count > capacity()) {
		Vector(count, value).swap(*this);
	} else {
		clear();
		std::fill(elements, elements + count, value);
		first_free = elements + count;
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::assign(std::initializer_list<T> ilist)
{
	if (ilist.size() > capacity()) {
		Vector(ilist).swap(*this);
	} else {
		clear();
		std::copy(ilist.begin(), ilist.end(), elements);
		first_free = elements + ilist.size();
	}
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::allocator_type
Vector<T, Allocator>::get_allocator() const
{
	return static_cast<const Allocator&>(*this);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::at(size_type pos)
{
	if (pos >= size())
		throw std::out_of_range("Vector::at()");
	return *(elements+pos);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::at(size_type pos) const
{
	if (pos >= size())
		throw std::out_of_range("Vector::at()");
	return *(elements+pos);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::operator[](size_type pos)
{
	return *(elements + pos);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::operator[](size_type pos) const
{
	return *(elements + pos);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::front()
{
	return *elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::front() const
{
	return *elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::back()
{
	return *(first_free-1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::back() const
{
	return *(first_free-1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::pointer
Vector<T, Allocator>::data() noexcept
{
	return elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_pointer
Vector<T, Allocator>::data() const noexcept
{
	return static_cast<const_pointer>(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::begin() noexcept
{
	return elements;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::begin() const noexcept
{
	return static_cast<const_iterator>(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cbegin() const noexcept
{
	return static_cast<const_iterator>(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::end() noexcept
{
	return first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::end() const noexcept
{
	return static_cast<const_iterator>(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cend() const noexcept
{
	return static_cast<const_iterator>(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rbegin() noexcept
{
	return static_cast<reverse_iterator>(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::rbegin() const noexcept
{
	return static_cast<const_reverse_iterator>(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::crbegin() const noexcept
{
	return static_cast<const_reverse_iterator>(first_free);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rend() noexcept
{
	return static_cast<reverse_iterator>(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::rend() const noexcept
{
	return static_cast<const_reverse_iterator>(elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::crend() const noexcept
{
	return static_cast<const_reverse_iterator>(elements);
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept
{
	return elements == first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::size() const noexcept
{
	return static_cast<size_type>(first_free - elements);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::max_size() const noexcept
{
	return static_cast<size_type>(0xffffffffUL / sizeof(T));
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::capacity() const noexcept
{
	return static_cast<size_type>(end_of_storage - elements);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(size_type new_cap)
{
	if (new_cap <= capacity())
		return ;

	moveToNewChunk(new_cap);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::shrink_to_fit()
{
	if (first_free != end_of_storage) {
		moveToNewChunk(size());
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::clear() noexcept
{
	doDestroy(elements, first_free);
	elements = first_free;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::insert(iterator pos, const T& value)
{
	if (first_free != end_of_storage) {
		Allocator::construct(first_free, *(first_free-1));
		++first_free;
		copyBackward(pos, first_free-2, first_free-1);
		Allocator::construct(pos, value);
	} else {
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;

		iterator new_start = Allocator::allocate(len);
		iterator new_finish = new_start;
		try {
			new_finish = std::uninitialized_copy(elements, pos, new_start);
			Allocator::construct(new_start, value);
			++new_finish;
			new_finish = std::uninitialized_copy(pos, first_free, new_finish);
		} catch (...) {
			doDestroy(new_start, new_finish);
			Allocator::deallocate(new_start, len);
			throw;
		}

		doDestroy(begin(), end());
		doDeallocate();

		elements = new_start;
		first_free = new_finish;
		end_of_storage = new_start + len;
	}
}

//template <typename T, typename Allocator>
//typename Vector<T, Allocator>::iterator
//Vector<T, Allocator>::insert(const_iterator pos, T&& value)
//{
//	cout << "T&&\n";
//	// insert(pos, std::move(value));
//	if (first_free != end_of_storage) {
//		Allocator::construct(first_free, *(first_free-1));
//		++first_free;
//		copyBackward(pos, first_free-2, first_free-1);
//		Allocator::construct(pos, value);
//	} else {
//
//	}
//}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::insert(iterator pos, size_type count, const T& value)
{
	if (count != 0) {
		if (size_type(end_of_storage - first_free) > 0) {
			T value_copy = value;
			const size_type elems_after = first_free - pos;
			iterator old_finish = first_free;
			if (elems_after > 0) {
				std::uninitialized_copy(first_free-count, first_free, first_free);
				first_free += count;
				std::copy_backward(pos, old_finish-count, old_finish);
				std::fill(pos, pos+count, value_copy);
			} else {
				std::uninitialized_fill_n(first_free, count-elems_after, value_copy);
				first_free += (count - elems_after);
				std::uninitialized_copy(pos, old_finish, first_free);
				first_free += elems_after;
				std::fill(pos, old_finish, value_copy);
			}
		} else {
			const size_type old_size = size();
			const size_type len = old_size + std::max(old_size, size_type(0));
			iterator new_start = Allocator::allocate(len);
			iterator new_finish = new_start;

			try {
				new_finish = std::uninitialized_copy(elements, pos, new_start);
				std::uninitialized_fill_n(new_finish, count, value);
				new_finish += count;
				new_finish = std::uninitialized_copy(pos, first_free, new_finish);
			} catch (...) {
				doDestroy(new_start, new_finish);
				Allocator::deallocate(new_start, len);
				throw ;
			}

			doDestroy(elements, first_free);
			doDeallocate();

			elements = new_start;
			first_free = new_finish;
			end_of_storage = new_start + len;
		}
	}
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::insert(iterator pos, std::initializer_list<T> ilist)
{

}

template <typename T, typename Allocator>
template <typename... Args>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::emplace(iterator pos, Args&&... args)
{
	auto n = first_free - pos;
	if ((first_free == capacity) || (pos < end_of_storage)) {
		// ...
	} else {
		::new ((void*)first_free) value_type(std::forward<Args>(args)...);
		++first_free;
	}
	// ...
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::erase(iterator pos)
{
	if (pos + 1 != end())
		std::copy(pos+1, first_free, pos);
	--first_free;
	Allocator::destroy(first_free);
	return pos;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::erase(iterator first, iterator last)
{
	iterator i = std::copy(last, first_free, first);
	doDestroy(i, first_free);
	first_free = first_free - (last - first);
	return first;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const T& value)
{
	if (first_free != end_of_storage) {
		Allocator::construct(first_free, value);
	} else {
		insert(end(), value);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(T&& value)
{
	emplace_back(std::move(value));
}

template <typename T, typename Allocator>
template <typename... Args>
void Vector<T, Allocator>::emplace_back(Args&&...args)
{

}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back()
{
	if (first_free > elements) {
		--first_free;
		Allocator::destroy(first_free);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_type new_sz)
{
	resize(new_sz, T());
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_type new_sz, const value_type& value)
{
	if (new_sz < size()) {
		erase(elements + new_sz, cend());
	} else {
		insert(cend(), new_sz - size(), value);
	}
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::swap(Vector& rhs) noexcept
{
	using std::swap;
	swap(elements, rhs.elements);
	swap(first_free, rhs.first_free);
	swap(end_of_storage, rhs.end_of_storage);
}

//  non-menber function

template <typename T, typename Alloc>
void swap(Vector<T, Alloc>& lhs, Vector<T, Alloc>& rhs) noexcept
{
	lhs.swap(rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, " "));
	return out;
}

template <typename T, typename Alloc>
bool operator==(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator!=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	return lhs.size() != rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator<(const Vector<T,Alloc>& lhs,
               const Vector<T,Alloc>& rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

template <typename T, typename Alloc>
bool operator>(const Vector<T,Alloc>& lhs,
               const Vector<T,Alloc>& rhs)
{
	return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator>=(const Vector<T,Alloc>& lhs,
                const Vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
}

}

#endif
