
namespace list_detail {

template <typename T, typename Pot, typename Ref>
typename ListIterator<T, Pot, Ref>::this_type
ListIterator<T, Pot, Ref>::prev() const noexcept
{
	return ListIterator<T, Pot, Ref>(nodeptr_->prev_);
}

template <typename T, typename Pot, typename Ref>
typename ListIterator<T, Pot, Ref>::this_type
ListIterator<T, Pot, Ref>::next() const noexcept
{
	return ListIterator<T, Pot, Ref>(nodeptr_->next_);
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>::ListIterator() noexcept
	: nodeptr_(nullptr)
{
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>::ListIterator(ListNode<T>* nodeptr) noexcept
	: nodeptr_(nodeptr)
{
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>::ListIterator(const iterator& rhs) noexcept
	: nodeptr_(rhs.nodeptr_)
{
}

template <typename T, typename Pot, typename Ref>
typename ListIterator<T, Pot, Ref>::reference
ListIterator<T, Pot, Ref>::operator*() const noexcept
{
	return nodeptr_->value_;
}

template <typename T, typename Pot, typename Ref>
typename ListIterator<T, Pot, Ref>::pointer
ListIterator<T, Pot, Ref>::operator->() const noexcept
{
	return &(operator*());
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>& ListIterator<T, Pot, Ref>::operator++() noexcept
{
	nodeptr_ = nodeptr_->next_;
	return *this;
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>& ListIterator<T, Pot, Ref>::operator++(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>& ListIterator<T, Pot, Ref>::operator--() noexcept
{
	nodeptr_ = nodeptr_->prev_;
	return *this;
}

template <typename T, typename Pot, typename Ref>
ListIterator<T, Pot, Ref>& ListIterator<T, Pot, Ref>::operator--(int) noexcept
{
	auto tmp = *this;
	++*this;
	return tmp;
}

template <typename T, typename Pot, typename Ref>
bool ListIterator<T, Pot, Ref>::operator==(const ListIterator<T, Pot, Ref>& rhs) const noexcept
{
	return nodeptr_ == rhs.nodeptr_;
}

template <typename T, typename Pot, typename Ref>
bool ListIterator<T, Pot, Ref>::operator!=(const ListIterator<T, Pot, Ref>& rhs) const noexcept
{
	return nodeptr_ != rhs.nodeptr_; 
}

} // list_detail 

// protected

template <typename T, typename Allocator>
typename List<T, Allocator>::link_type
List<T, Allocator>::getNode()
{
	return node_alloc_.allocate(1);
}

template <typename T, typename Allocator>
void List<T, Allocator>::putNode(link_type p)
{
	node_alloc_.deallocate(p, 1);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::link_type
List<T, Allocator>::createNode(const T& value)
{
	link_type p = getNode();
	Allocator::construct(&(p->value_), value);
	return p;
}

template <typename T, typename Allocator>
void List<T, Allocator>::destroyNode(link_type p)
{
	Allocator::destroy(&(p->value_));
	putNode(p);
}

template <typename T, typename Allocator>
void List<T, Allocator>::emptyInitializer()
{
	node_ = getNode();
	node_->prev_ = node_;
	node_->next_ = node_;
	size_ = 0;
}

// transfer [first, last) to pos
template <typename T, typename Allocator>
void List<T, Allocator>::transfer(const_iterator pos, const_iterator first, const_iterator last)
{
	if (pos != last) {
		last.nodeptr_->prev_->next_ = pos.nodeptr_;
		first.nodeptr_->prev_->next_ = last.nodeptr_;
		pos.nodeptr_->prev_->next_ = first.nodeptr_;
		auto tmp = pos.nodeptr_->prev_;
		pos.nodeptr_->prev_ = last.nodeptr_->prev_;
		last.nodeptr_->prev_ = first.nodeptr_->prev_;
		first.nodeptr_->prev_ = tmp;
	}
}

// public

template <typename T, typename Allocator>
List<T, Allocator>::List(const Allocator& alloc)
	: Allocator(alloc)
{
	emptyInitializer();
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_type n)
	: List(n, T())
{
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_type count, const T& value, const Allocator& alloc)
	: Allocator(alloc)
{
	emptyInitializer();
	insert(cend(), count, value); // size_ incremented in insert().
}

template <typename T, typename Allocator>
template <class InputIterator, typename>
List<T, Allocator>::List(InputIterator first, InputIterator last, const Allocator& alloc)
	: Allocator(alloc)
{
	emptyInitializer();
	insert(cend(), first, last); // size_ incremented in insert().
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const List& rhs)
	: List(rhs.begin(), rhs.end())
{
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List&& rhs)
{
	this->swap(rhs);
}

template <typename T, typename Allocator>
List<T, Allocator>::List(std::initializer_list<T> init, const Allocator& alloc)
	: List(init.begin(), init.end())
{
}

template <typename T, typename Allocator>
List<T, Allocator>::~List()
{
	clear();
	putNode(node_);
	size_ = 0;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(const List<T, Allocator>& rhs)
{
	this->swap(rhs());
	return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(List<T, Allocator>&& rhs)
{
	if (this != &rhs) {
		this->swap(rhs);
	}
	return *this;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(std::initializer_list<T> rhs)
{
	this->swap(List(rhs.begin(), rhs.end()));
}

template <typename T, typename Allocator>
template <class InputIterator, typename>
void List<T, Allocator>::assign(InputIterator first, InputIterator last)
{
	clear();
	insert(cend(), first, last);
}

template <typename T, typename Allocator>
void List<T, Allocator>::assign(size_type n, const T& t)
{
	clear();
	insert(cend(), n, t);
}

template <typename T, typename Allocator>
void List<T, Allocator>::assign(std::initializer_list<T> init)
{
	assign(init.begin(), init.end());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::allocator_type
List<T, Allocator>::get_allocator() const noexcept
{
	return allocator_type();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::begin() noexcept
{
	return iterator(node_->next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::begin() const noexcept
{
	return const_iterator(node_->next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::end() noexcept
{
	return iterator(node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::end() const noexcept
{
	return const_iterator(node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator
List<T, Allocator>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator
List<T, Allocator>::rend() noexcept
{
	return reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
 List<T, Allocator>::cbegin() const noexcept
{
	return const_iterator(node_->next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::cend() const noexcept
{
	return const_iterator(node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::crbegin() const noexcept
{
	return rbegin();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::crend() const noexcept
{
	return rend();
}

template <typename T, typename Allocator>
bool List<T, Allocator>::empty() const noexcept
{
	return begin() == end();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::size_type
List<T, Allocator>::size() const noexcept // todo: don't use cached size.
{
	return size_;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::size_type
List<T, Allocator>::maxsize() const noexcept
{
	return static_cast<size_type>(0xffffffffUL / sizeof(T));
}

template <typename T, typename Allocator>
void List<T, Allocator>::resize(size_type sz)
{
	resize(sz, T());
}

template <typename T, typename Allocator>
void List<T, Allocator>::resize(size_type sz, const T& c)
{
	if (sz > size()) {
		insert(cend(), sz - size(), c);
	} else if (sz < size()) {
		auto iter = cbegin();
		std::advance(iter, sz);
		erase(iter, cend());
	} else {
		// do nothing.
	}
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference
List<T, Allocator>::front()
{
	if (empty()) {
		throw "List::front(): List is empty";
	}
	return *begin();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference
List<T, Allocator>::front() const
{
	if (empty()) {
		throw "List::front(): List is empty";
	}
	return *cbegin();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference
List<T, Allocator>::back()
{
	if (empty()) {
		throw "List::back(): List is empty";
	}
	return *rbegin();
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference
List<T, Allocator>::back() const
{
	if (empty()) {
		throw "List::back(): List is empty";
	}
	return *crbegin();
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::reference
List<T, Allocator>::emplace_front(Args&&... args)
{
	emplace(cbegin(), std::forward<Args>(args)...);
}

template <typename T, typename Allocator>
void List<T, Allocator>::pop_front()
{
	erase(cbegin());
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::reference
List<T, Allocator>::emplace_back(Args&&... args)
{
	emplace(cend(), std::forward<Args>(args)...);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(const T& x)
{
	insert(cbegin(), x);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(T&& x)
{
	insert(cbegin(), std::move(x));
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(const T& x)
{
	insert(cend(), x);
}
    
template <typename T, typename Allocator>
void List<T, Allocator>::push_back(T&& x)
{
	insert(cend(), std::move(x));
}
    
template <typename T, typename Allocator>
void List<T, Allocator>::pop_back()
{
	auto tmp = cend();
	--tmp;
	erase(tmp);
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::iterator
List<T, Allocator>::emplace(const_iterator pos, Args&&... args)
{
	link_type tmp = createNode(T(std::forward<Args>(args)...));
	tmp->next_ = pos.nodeptr_;
	tmp->prev_ = pos.nodeptr_->prev_;
	pos.nodeptr_->prev_->next_ = tmp;
	pos.nodeptr_->prev_ = tmp;
	++size_;
	return iterator(tmp);
}
    
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, const T& x)
{
	auto tmp = x;
	return emplace(pos, std::move(tmp));
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, T&& x)
{
	return emplace(pos, std::move(x));
}
    
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, size_type n, const T& x)
{
	auto ret = insert(pos, x);
	for (size_type i = 1; i < n; ++i) {
		insert(pos, x);
	}
	return ret;
}
    
template <typename T, typename Allocator>
template <class InputIterator, typename>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
	auto ret = insert(pos, *first);
	for (auto iter = ++first; iter != last; ++iter) {
		insert(pos, *iter);
	}
	return ret;
}
        
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> il)
{
	return insert(pos, il.begin(), il.end());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::erase(const_iterator pos)
{
	auto next_node = pos.nodeptr_->next_;
	auto prev_node = pos.nodeptr_->prev_;
	prev_node->next_ = next_node;
	next_node->prev_ = prev_node;
	destroyNode(pos.nodeptr_);
	--size_;
	return iterator(next_node);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::erase(const_iterator first, const_iterator last)
{
	while (first != last) {
		first = erase(first);
	}
	return iterator(last.nodeptr_);
}

template <typename T, typename Allocator>
void List<T, Allocator>::swap(List& rhs)
{
	using std::swap;
	swap(size_, rhs.size_);
	swap(node_, rhs.node_);
	swap(node_alloc_, rhs.node_alloc_);
}

template <typename T, typename Allocator>
void List<T, Allocator>::clear() noexcept
{
	link_type cur = node_->next_;
	while (cur != node_) {
		link_type tmp = cur;
		cur = cur->next_;
		destroyNode(tmp);
	}
	node_->prev_ = node_;
	node_->next_ = node_;
	size_ = 0;
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>& x)
{
	if (!x.empty()) {
		transfer(pos, x.begin(), x.end());
	}
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x)
{
	splice(pos, std::move(x));
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&, const_iterator i)
{
	iterator j = i;
	++j;
	if (pos == i || pos == j) {
		return ;
	}
	transfer(pos, i, j);
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x, const_iterator i)
{
	splice(pos, std::move(x), i);
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&,
                                const_iterator first, const_iterator last)
{
	if (first != last) {
		transfer(pos, first, last);
	}
}
  
template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x,
                                const_iterator first, const_iterator last)
{
	splice(pos, std::move(x), first, last);
}

template <typename T, typename Allocator>
void List<T, Allocator>::remove(const T& value)
{
	remove_if(
		[&](T v){ return v == value; }
	);
}

template <typename T, typename Allocator>
template <class UnaryPredicate>
void List<T, Allocator>::remove_if(UnaryPredicate pred)
{
	auto p = cbegin();
	while (p != cend()) {
		auto next = p;
		++next;
		if (pred(*p)) {
			erase(p);
		}
		p = next;
	}
}

template <typename T, typename Allocator>
void List<T, Allocator>::unique()
{
	unique(std::equal_to<T>());
}

template <typename T, typename Allocator>
template <class BinaryPredicate>
void List<T, Allocator>::unique(BinaryPredicate binary_pred)
{
	if (size() == 0) {
		return ;
	}
	auto first = cbegin();
	auto next = first;
	while (++next != cend()) {
		if (binary_pred(*first, *next)) {
			erase(first);
		} else {
			first = next;
		}
		next = first;
	}
}

template <typename T, typename Allocator>
void List<T, Allocator>::merge(List<T, Allocator>& x)
{
	merge(x, std::less<T>());
}

template <typename T, typename Allocator>
void List<T, Allocator>::merge(List<T, Allocator>&& x)
{
	merge(std::move(x), std::less<T>());
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::merge(List<T, Allocator>& x, Compare comp)
{
	auto p = cbegin(), q = x.cbegin();
	while (p != cend() && q != x.cend()) {
		if (comp(*p, *q)) {
			auto next = q;
			transfer(p, q, ++next);
			q = next;
		} else {
			++p;
		}
	}
	
	if (q != x.cend()) { // move the rest of x to the end of list.
		transfer(cend(), q, x.cend());
	}
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::merge(List<T, Allocator>&& x, Compare comp)
{
	merge(std::move(x), comp);
}

template <typename T, typename Allocator>
void List<T, Allocator>::sort()
{
	sort(std::less<T>());
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::sort(Compare comp)
{
	if (size() == 0 || size() == 1) {
		return ;
	}
	// TODO
}

template <typename T, typename Allocator>
void List<T, Allocator>::reverse() noexcept
{
	if (size() == 0 || size() == 1) {
		return ;
	}
	auto p = cbegin();
	++p;
	while (p != cend()) {
		auto old = p;
		++p;
		transfer(begin(), old, p);
	}
}

// non-member

template <class T, class Allocator>
bool operator==(const List<T, Allocator>& x, const List<T, Allocator>& y)
{
	if (x.size() != y.size()) {
		return false;
	} else {
		for (auto xi = x.cbegin(), yi = y.cbegin(); xi != x.cend(); ++xi, ++yi) {
			if (*xi != *yi) {
				return false;
			}
		}
	}
	return true;
}

template <class T, class Allocator>
bool operator< (const List<T, Allocator>& x, const List<T, Allocator>& y)
{
	if (x.size() != y.size()) {
		return x.size() < y.size();
	} else {
		for (auto xi = x.cbegin(), yi = y.cbegin(); xi != x.cend(); ++xi, ++yi) {
			if (*xi > *yi) {
				return false;
			}
		}
	}
	return true;
}

template <class T, class Allocator>
bool operator!=(const List<T, Allocator>& x, const List<T, Allocator>& y)
{
    return !(x == y);
}

template <class T, class Allocator>
bool operator> (const List<T, Allocator>& x, const List<T, Allocator>& y)
{
    return y < x;
}

template <class T, class Allocator>
bool operator>=(const List<T, Allocator>& x, const List<T, Allocator>& y)
{
    return !(x < y);
}

template <class T, class Allocator>
bool operator<=(const List<T, Allocator>& x, const List<T, Allocator>& y)
{
    return !(x > y);
}

template <class T, class Allocator>
void swap(List<T, Allocator>& x, List<T, Allocator>& y)
{
    x.swap(y);
}

