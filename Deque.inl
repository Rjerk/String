#include <cassert> 
#include <iostream>

using std::cout;

namespace mystl {

namespace deque_detail {

template <typename T, typename Ptr, typename Ref>
DequeIterator<T, Ptr, Ref>::DequeIterator() noexcept
	: cur_(nullptr), first_(nullptr), last_(nullptr), node_(nullptr)
{
}

template <typename T, typename Ptr, typename Ref>
DequeIterator<T, Ptr, Ref>::DequeIterator(map_pointer mp) noexcept
	: cur_(nullptr), first_(*mp), last_(first_ + bufferSize()), node_(mp)
{
}

template <typename T, typename Ptr, typename Ref>
DequeIterator<T, Ptr, Ref>::DequeIterator(const iterator& rhs) noexcept // for iterator conversion.
	: cur_(rhs.cur_), first_(rhs.first_), last_(rhs.last_), node_(rhs.node_)
{
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::reference
DequeIterator<T, Ptr, Ref>::operator*() const noexcept
{
	return *cur_;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::pointer
DequeIterator<T, Ptr, Ref>::operator->() const noexcept
{
	return &(operator*());
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::reference
DequeIterator<T, Ptr, Ref>::operator[](difference_type n) noexcept
{
	return *(*this + n);
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator==(const self& rhs) const noexcept
{
	return cur_ == rhs.cur_;
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator!=(const self& rhs) const noexcept
{
	return !(*this == rhs);
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator< (const self& rhs) const noexcept
{
	return (node_ == rhs.node_) ? (cur_ < rhs.cur_) : (node_ < rhs.node_);
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator> (const self& rhs) const noexcept
{
	return rhs < *this;
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator<=(const self& rhs) const noexcept
{
	return !(*this > rhs);
}

template <typename T, typename Ptr, typename Ref>
bool DequeIterator<T, Ptr, Ref>::operator>=(const self& rhs) const noexcept
{
	return !(*this < rhs);
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator++() noexcept
{
	++cur_;
	if (cur_ == last_) {
		setNode(node_+1);
		cur_ = first_;
	}
	return *this;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator--() noexcept
{
	if (cur_ == first_) {
		setNode(node_-1); // FIXME: if first node in map.
		cur_ = last_;
	}
	--cur_;
	return *this;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator--(int) noexcept
{
	auto tmp = *this;
	--*this;
	return tmp;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::difference_type
DequeIterator<T, Ptr, Ref>::operator-(const self& rhs) const noexcept
{
	return bufferSize() * (node_ - rhs.node_ - 1) + (cur_ - first_) + (rhs.last_ - rhs.cur_);
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self
DequeIterator<T, Ptr, Ref>::operator-(difference_type n) noexcept
{
	auto tmp = *this;
	return tmp -= n;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self
DequeIterator<T, Ptr, Ref>::operator+(difference_type n) noexcept
{
	auto tmp = *this;
	return tmp += n;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator+=(difference_type n) noexcept
{
	auto offset = n + (cur_ - first_);
	if (offset >= 0 && offset < bufferSize()) { // same buffer.
		cur_ += n;
	} else {
		auto node_offset = offset > 0 ? offset / bufferSize()
									  : -((offset - 1) / bufferSize()) - 1;
		setNode(node_ + node_offset); // FIXME: if out of boundary.
		cur_ = first_ + (offset - node_offset * bufferSize());
	}
	return *this;
}

template <typename T, typename Ptr, typename Ref>
typename DequeIterator<T, Ptr, Ref>::self&
DequeIterator<T, Ptr, Ref>::operator-=(difference_type n) noexcept
{
	return (*this += (-n));
}


template <typename T, typename Ptr, typename Ref>
size_t DequeIterator<T, Ptr, Ref>::bufferSize()
{
	return sizeof(T) < BUFSIZE ? static_cast<size_t>(BUFSIZE / sizeof(T))
							   : static_cast<size_t>(1);
}

template <typename T, typename Ptr, typename Ref>
void DequeIterator<T, Ptr, Ref>::setNode(map_pointer new_node)
{
	node_ = new_node;
	first_ = *new_node;
	last_ = first_ + static_cast<difference_type>(bufferSize());
}

} // deque detail.

template <typename T, typename Allocator>
void Deque<T, Allocator>::createMapAndNode(size_type elem_num)
{
	size_t node_num = elem_num / deque_detail::DequeIterator<T>::bufferSize() + 1;
	mapsize_ = std::max(node_num + 2, deque_detail::MIN_NODE_NUM); // +2 is for expandation.

	auto map_ = map_alloc_.allocate(mapsize_);
	auto map_start = map_ + (mapsize_ - node_num) / 2; // middle of map.
	auto map_finish = map_start + node_num - 1;

	map_pointer map_cur = map_start;
	try {
		for ( ; map_cur <= map_finish; ++map_cur) {
			*map_cur = Allocator::allocate(deque_detail::DequeIterator<T>::bufferSize());
		}
	} catch (...) {
		while (map_cur != map_finish) {
			--map_cur;
			Allocator::deallocate(*map_cur, deque_detail::DequeIterator<T>::bufferSize());
			*map_cur = nullptr;
		}
	}
	start_.setNode(map_start);
	finish_.setNode(map_finish);
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::emptyInitializer()
{
	createMapAndNode(0);
	start_.cur_ = start_.first_;
	finish_.cur_ = finish_.first_;
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::fillInitializer(size_t n, value_type value)
{
	createMapAndNode(n);
	start_.cur_ = start_.first_;
	finish_.cur_ = finish_.first_ + n % deque_detail::DequeIterator<T>::bufferSize();

	map_pointer cur = start_.node_;
	for ( ; cur < finish_.node_; ++cur) {
		// fill every buffer.
		std::uninitialized_fill(*cur, *cur + deque_detail::DequeIterator<T>::bufferSize(), value);
	}
	
	// last redundant buffer.
	if (start_ != finish_) {
		std::uninitialized_fill(finish_.first_, finish_.cur_, value);
	}
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(const Allocator& alloc)
	:  Allocator(alloc), start_(), finish_(), map_(nullptr), mapsize_(0)
{
	emptyInitializer();
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(size_type n)
	: Deque(n, T())
{
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(size_type n, const T& value, const Allocator& alloc)
	: Allocator(alloc), start_(), finish_(), map_(nullptr), mapsize_(0)
{
	fillInitializer(n, value);
}

template <typename T, typename Allocator>
template <typename InputIterator, typename>
Deque<T, Allocator>::Deque(InputIterator first, InputIterator last,const Allocator& alloc)
{
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(const Deque<T, Allocator>& x)
{
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(Deque&&)
{
}

template <typename T, typename Allocator>
Deque<T, Allocator>::Deque(std::initializer_list<T>, const Allocator& alloc)
{
	
}

template <typename T, typename Allocator>
Deque<T, Allocator>::~Deque()
{
	if (map_) {
		clear();
		for (int i = 0; i < mapsize_; ++i) {
			Allocator::deallocate(*start_.node_, deque_detail::DequeIterator<T>::bufferSize());
		}
		map_alloc_.deallocate(map_, mapsize_);
	} 
}
	
template <typename T, typename Allocator>
Deque<T,Allocator>& Deque<T, Allocator>::operator=(const Deque<T, Allocator>& x)
{
	
}

template <typename T, typename Allocator>
Deque<T,Allocator>& Deque<T, Allocator>::operator=(Deque<T, Allocator>&& x)
{
	
}

template <typename T, typename Allocator>
Deque<T, Allocator>& Deque<T, Allocator>::operator=(std::initializer_list<T>)
{
	
}


template <typename T, typename Allocator>
template <typename InputIterator, typename>
void Deque<T, Allocator>::assign(InputIterator first, InputIterator last)
{
	
}


template <typename T, typename Allocator>
void Deque<T, Allocator>::assign(size_type n, const T& t)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::assign(std::initializer_list<T>)
{
	
}


template <typename T, typename Allocator>
typename Deque<T, Allocator>::allocator_type
Deque<T, Allocator>::get_allocator() const noexcept
{
	
}


template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::begin() noexcept
{
	return start_;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator
Deque<T, Allocator>::begin() const noexcept
{
	return static_cast<const_iterator>(start_);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::end() noexcept
{
	return finish_;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator
Deque<T, Allocator>::end() const noexcept
{
	return static_cast<const_iterator>(finish_);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reverse_iterator
Deque<T, Allocator>::rbegin() noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator
Deque<T, Allocator>::rbegin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reverse_iterator
Deque<T, Allocator>::rend() noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator
Deque<T, Allocator>::rend() const noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator
Deque<T, Allocator>::cbegin() const noexcept
{
	return static_cast<const_iterator>(start_);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator
Deque<T, Allocator>::cend() const noexcept
{
	return static_cast<const_iterator>(finish_);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator
Deque<T, Allocator>::crbegin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator
Deque<T, Allocator>::crend() const noexcept
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::size_type
Deque<T, Allocator>::size() const noexcept
{
	return finish_ - start_;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::size_type
Deque<T, Allocator>::max_size() const noexcept
{
	return static_cast<size_type>(0xffffffffUL / sizeof(T));
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::resize(size_type sz)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::resize(size_type sz, const T& c)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::shrink_to_fit()
{
	
}

template <typename T, typename Allocator>
bool Deque<T, Allocator>::empty() const noexcept
{
	return start_ == finish_;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference
Deque<T, Allocator>::operator[](size_type n)
{
	return start_[n];
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference
Deque<T, Allocator>::operator[](size_type n) const
{
	return static_cast<const_reference>(start_[n]);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference
Deque<T, Allocator>::at(size_type n)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference
Deque<T, Allocator>::at(size_type n) const
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference
Deque<T, Allocator>::front()
{
	return *start_;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference
Deque<T, Allocator>::front() const
{
	return static_cast<const_reference>(*start_);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference
Deque<T, Allocator>::back()
{
	return *(finish_ - 1);
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference
Deque<T, Allocator>::back() const
{
	
}


template <typename T, typename Allocator>
template <typename... Args>
void Deque<T, Allocator>::emplace_front(Args&&... args)
{
	
}

template <typename T, typename Allocator>
template <typename... Args>
void Deque<T, Allocator>::emplace_back(Args&&... args)
{
	
}

template <typename T, typename Allocator>
template <typename... Args>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::emplace(const_iterator position, Args&&... args)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_front(const T& x)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_front(T&& x)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_back(const T& x)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_back(T&& x)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::insert(const_iterator position, const T& x)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::insert(const_iterator position, T&& x)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::insert(const_iterator position, size_type n, const T& x)
{
	
}

template <typename T, typename Allocator>
template <typename InputIterator, typename>
typename Deque<T, Allocator>::iterator
 Deque<T, Allocator>::insert (const_iterator position, InputIterator first, InputIterator last)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::insert(const_iterator position, std::initializer_list<T>)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::pop_front()
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::pop_back()
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::erase(const_iterator position)
{
	
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator
Deque<T, Allocator>::erase(const_iterator first, const_iterator last)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::swap(Deque<T, Allocator>&)
{
	
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::clear() noexcept
{
	
}


template <typename T, typename Allocator>
bool operator==(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	//
}

template <typename T, typename Allocator>
bool operator< (const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	//
}

template <typename T, typename Allocator>
bool operator!=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
bool operator> (const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	return y < x;
}

template <typename T, typename Allocator>
bool operator>=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	return !(x < y);
}

template <typename T, typename Allocator>
bool operator<=(const Deque<T, Allocator>& x, const Deque<T, Allocator>& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
void swap(Deque<T, Allocator>& x, Deque<T, Allocator>& y)
{
	x.swap(y);
}
	
}
