
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

template <typename T, typename Allocator>
typename List<T, Allocator>::link_type
List<T, Allocator>::getNode()
{
	return node_alloc.allocate(1);
}

template <typename T, typename Allocator>
void List<T, Allocator>::putNode(link_type p)
{
	return node_alloc.deallocate(p);
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


template <typename T, typename Allocator>
List<T, Allocator>::List(const Allocator& alloc)
	: Allocator(alloc)
{
	emptyInitializer();
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_type n)
{
	
}


template <typename T, typename Allocator>
List<T, Allocator>::List(size_type count, const T& value, const Allocator& alloc)
	: size_(count), Allocator(alloc)
{
}

template <typename T, typename Allocator>
template <class InputIterator>
List<T, Allocator>::List(InputIterator first, InputIterator last, const Allocator& alloc)
{
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const List& rhs)
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>::List(List&& rhs)
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>::List(std::initializer_list<T> init, const Allocator& alloc)
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>::~List()
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(const List<T, Allocator>& rhs)
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(List<T, Allocator>&& rhs)
{
	
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(std::initializer_list<T>)
{
	
}

template <typename T, typename Allocator>
template <class InputIterator>
void List<T, Allocator>::assign(InputIterator first, InputIterator last)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::assign(size_type n, const T& t)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::assgin(std::initializer_list<T> init)
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::allocator_type
List<T, Allocator>::get_allocator() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::begin() noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::begin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::end() noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::end() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator
List<T, Allocator>::rbegin() noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::rbegin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator
List<T, Allocator>::rend() noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::rend() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
 List<T, Allocator>::cbegin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator
List<T, Allocator>::cend() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::crbegin() const noexcept
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::crend() const noexcept
{
	
}

template <typename T, typename Allocator>
bool List<T, Allocator>::empty() const noexcept
{
	return size_ == 0;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::size_type
List<T, Allocator>::size() const noexcept
{
	return size_;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::size_type
List<T, Allocator>::maxsize() const noexcept
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::resize(size_type sz)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::resize(size_type sz, const T& c)
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference List<T, Allocator>::front()
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference
List<T, Allocator>::front() const
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reference
List<T, Allocator>::back()
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reference
List<T, Allocator>::back() const
{
	
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::reference
List<T, Allocator>::emplace_front(Args&&... args)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::pop_front()
{
	
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::reference
List<T, Allocator>::emplace_back(Args&&... args)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(const T& x)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(T&& x)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(const T& x)
{
	
}
    
template <typename T, typename Allocator>
void List<T, Allocator>::push_back(T&& x)
{
	
}
    
template <typename T, typename Allocator>
void List<T, Allocator>::pop_back()
{
	
}

template <typename T, typename Allocator>
template <class... Args>
typename List<T, Allocator>::iterator
List<T, Allocator>::emplace(const iterator pos, Args&&... args)
{
	
}
    
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, const T& x)
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, T&& x)
{
	
}
    
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, size_type n, const T& x)
{
	
}
    
template <typename T, typename Allocator>
template <class InputIterator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
	
}
        
template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> il)
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::erase(const_iterator pos)
{
	
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator
List<T, Allocator>::erase(const_iterator pos, const_iterator last)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::swap(List& rhs)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::clear() noexcept
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>& x)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>& x, const_iterator i)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x, const_iterator i)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>& x,
            const_iterator first, const_iterator last)
{
	
}
  
template <typename T, typename Allocator>
void List<T, Allocator>::splice(const_iterator pos, List<T, Allocator>&& x,
            const_iterator first, const_iterator last)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::remove(const T& value)
{
	
}

template <typename T, typename Allocator>
template <class Predicate>
void List<T, Allocator>::remove_if(Predicate pred)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::unique()
{
	
}

template <typename T, typename Allocator>
template <class BinaryPredicate>
void List<T, Allocator>::unique(BinaryPredicate binary_pred)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::merge(List<T, Allocator>& x)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::merge(List<T, Allocator>&& x)
{
	
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::merge(List<T, Allocator>& x, Compare comp)
{
	
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::merge(List<T, Allocator>&& x, Compare comp)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::sort()
{
	
}

template <typename T, typename Allocator>
template <class Compare>
void List<T, Allocator>::sort(Compare comp)
{
	
}

template <typename T, typename Allocator>
void List<T, Allocator>::reverse() noexcept
{
	
}

// non-member

template <class T, class Allocator>
bool operator==(const List<T, Allocator>& x, const List<T, Allocator>& y)
{

}

template <class T, class Allocator>
bool operator< (const List<T, Allocator>& x, const List<T, Allocator>& y)
{
	
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

