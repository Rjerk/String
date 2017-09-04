#ifndef DEQUE_H
#define DEQUE_H

#include <initializer_list>
#include <memory>
#include "Iterator.h"

namespace mystl {

namespace deque_detail {

constexpr size_t BUFSIZE = 256; // (bytes)
constexpr size_t MIN_NODE_NUM = 8;

template <typename T, typename Ptr = T*, typename Ref = T&>
class DequeIterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = Ptr;
	using reference = Ref;
	using iterator = DequeIterator<T, T*, T&>;
	using const_iterator = DequeIterator<T, const T*, const T&>;
	using self = DequeIterator<T, Ptr, Ref>;
	using map_pointer = T**;

	DequeIterator() noexcept;
	DequeIterator(map_pointer mp) noexcept;
    DequeIterator(const iterator& rhs) noexcept; // for iterator -> const_iterator

    reference operator*() const noexcept;
	pointer operator->() const noexcept;
	reference operator[](difference_type n) noexcept;
	bool operator==(const self& rhs) const noexcept;
	bool operator!=(const self& rhs) const noexcept;
	bool operator< (const self& rhs) const noexcept;
	bool operator> (const self& rhs) const noexcept;
	bool operator<=(const self& rhs) const noexcept;
	bool operator>=(const self& rhs) const noexcept;
	self& operator++() noexcept;
	self& operator++(int) noexcept;
	self& operator--() noexcept;
	self& operator--(int) noexcept;
	difference_type operator-(const self& rhs) const noexcept;
	self  operator-(difference_type n) noexcept;
	self  operator+(difference_type n) noexcept;
	self& operator+=(difference_type n) noexcept;
	self& operator-=(difference_type n) noexcept;

	static size_t bufferSize();
	void setNode(map_pointer new_node);

	// pointer to buffer.
	pointer cur_; // first free.
	pointer first_;
	pointer last_; // after the last element.
	// pointer to map.
	map_pointer node_;
};

}

template <typename T, typename Allocator = std::allocator<T>>
class Deque : private Allocator {
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
	using iterator = deque_detail::DequeIterator<T, T*, T&>;
	using const_iterator = deque_detail::DequeIterator<T, const T*, const T&>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	
private:
	void createMapAndNode(size_type elem_num);
	void emptyInitializer();
	void fillInitializer(size_type n, value_type value);
	
protected:
	using map_pointer = pointer *;

	iterator start_;
	iterator finish_;
	map_pointer map_;
	size_type mapsize_;
	
	std::allocator<pointer> map_alloc_;
public:
	explicit Deque(const Allocator& = Allocator());
	explicit Deque(size_type n);
	Deque(size_type n, const T& value, const Allocator& = Allocator());
	template <typename InputIterator, typename = RequireInputIterator<InputIterator>>
	  Deque(InputIterator first, InputIterator last,const Allocator& = Allocator());
	Deque(const Deque<T,Allocator>& x);
	Deque(Deque&&);
	Deque(std::initializer_list<T>, const Allocator& = Allocator());
	
	~Deque();
	
	Deque<T,Allocator>& operator=(const Deque<T, Allocator>& x);
	Deque<T,Allocator>& operator=(Deque<T, Allocator>&& x);
	Deque& operator=(std::initializer_list<T>);

	template <typename InputIterator, typename = RequireInputIterator<InputIterator>>
	  void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const T& t);
	void assign(std::initializer_list<T>);

	allocator_type get_allocator() const noexcept;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;
	reverse_iterator rbegin() noexcept;
	const_reverse_iterator rbegin() const noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator rend() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend() const noexcept;

	size_type size() const noexcept;
	size_type max_size() const noexcept;
	void resize(size_type sz);
	void resize(size_type sz, const T& c);
	void shrink_to_fit();
	bool empty() const noexcept;

	reference operator[](size_type n);
	const_reference operator[](size_type n) const;
	reference at(size_type n);
	const_reference at(size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	template <typename... Args> void emplace_front(Args&&... args);
	template <typename... Args> void emplace_back(Args&&... args);
	template <typename... Args> iterator emplace(const_iterator position, Args&&... args);
	void push_front(const T& x);
	void push_front(T&& x);
	void push_back(const T& x);
	void push_back(T&& x);
	iterator insert(const_iterator position, const T& x);
	iterator insert(const_iterator position, T&& x);
	iterator insert(const_iterator position, size_type n, const T& x);
	template <typename InputIterator, typename = RequireInputIterator<InputIterator>>
	  iterator insert (const_iterator position, InputIterator first, InputIterator last);
	iterator insert(const_iterator position, std::initializer_list<T>);
	void pop_front();
	void pop_back();
	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);
	void swap(Deque<T, Allocator>&);
	void clear() noexcept;
};

template <typename T, typename Allocator>
bool operator==(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
bool operator< (const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
bool operator!=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
bool operator> (const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
bool operator>=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
bool operator<=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y);

template <typename T, typename Allocator>
void swap(Deque<T, Allocator>& x, Deque<T, Allocator>& y);

}

#include "Deque.inl"

#endif
