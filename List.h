#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <utility>

#include "Memory.h"
#include "Iterator.h" 

namespace mystl {

namespace list_detail {

template <typename T>
struct ListNode {
	T value_;
	ListNode * prev_;
	ListNode * next_;
};

template <typename T, typename Pot, typename Ref>
class ListIterator {
public:
	using iterator_category = bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = Pot;
	using reference = Ref;
	using node_type = ListNode<T>;
	using this_type = ListIterator<T, Pot, Ref>;

	this_type prev() const noexcept;
	this_type next() const noexcept;

    ListIterator() noexcept;
    ListIterator(ListNode<T>* nodeptr) noexcept;
    reference operator*() const noexcept;
	pointer operator->() const noexcept;
	ListIterator<T, Pot, Ref>& operator++() noexcept;
	ListIterator<T, Pot, Ref>& operator++(int) noexcept;
	ListIterator<T, Pot, Ref>& operator--() noexcept;
	ListIterator<T, Pot, Ref>& operator--(int) noexcept;
	bool operator==(const ListIterator<T, Pot, Ref>& rhs) const noexcept;
	bool operator!=(const ListIterator<T, Pot, Ref>& rhs) const noexcept;
private:
	node_type* nodeptr_;
};

}

template <typename T, typename Allocator = std::allocator<T>>
class List : private Allocator {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = list_detail::ListIterator<T, T*, T&>;
    using const_iterator = list_detail::ListIterator<T, const T*, const T&>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<iterator>;

protected:
	using node_type = list_detail::ListNode<T>;
	using link_type = node_type *;
	using NodeAllocator = std::allocator<node_type>;
	NodeAllocator node_alloc;

	link_type getNode();
	void putNode(link_type p);
	link_type createNode(const T& value);
	void destroyNode(link_type p);
	void emptyInitializer();

private:
	link_type node_;
    size_type size_;

public:
    explicit List(const Allocator& alloc = Allocator());
    explicit List(size_type n);
    List(size_type count, const T& value, const Allocator& alloc = Allocator());
    template <class InputIterator>
	List(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());

    List(const List& rhs);
    List(List&& rhs);
    List(std::initializer_list<T> init, const Allocator& alloc = Allocator());
    ~List();

    List<T, Allocator>& operator=(const List<T, Allocator>& rhs);
    List<T, Allocator>& operator=(List<T, Allocator>&& rhs);
    List& operator=(std::initializer_list<T>);

    template <class InputIterator> void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const T& t);
    void assgin(std::initializer_list<T> init);

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

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type maxsize() const noexcept;
    void resize(size_type sz);
    void resize(size_type sz, const T& c);

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    template <class... Args> reference emplace_front(Args&&... args);
    void pop_front();
    template <class... Args> reference emplace_back(Args&&... args);
    void push_front(const T& x);
    void push_front(T&& x);
    void push_back(const T& x);
    void push_back(T&& x);
    void pop_back();

    template <class... Args> iterator emplace(const iterator pos, Args&&... args);
    iterator insert(const_iterator pos, const T& x);
    iterator insert(const_iterator pos, T&& x);
    iterator insert(const_iterator pos, size_type n, const T& x);
    template <class InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last);
    iterator insert(const_iterator pos, std::initializer_list<T> il);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator pos, const_iterator last);
    void swap(List& rhs);
    void clear() noexcept;

    void splice(const_iterator pos, List<T, Allocator>& x);
    void splice(const_iterator pos, List<T, Allocator>&& x);
    void splice(const_iterator pos, List<T, Allocator>& x, const_iterator i);
    void splice(const_iterator pos, List<T, Allocator>&& x, const_iterator i);
    void splice(const_iterator pos, List<T, Allocator>& x,
                const_iterator first, const_iterator last);
    void splice(const_iterator pos, List<T, Allocator>&& x,
                const_iterator first, const_iterator last);

    void remove(const T& value);
    template <class Predicate> void remove_if(Predicate pred);

    void unique();
    template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred);

    void merge(List<T, Allocator>& x);
    void merge(List<T, Allocator>&& x);

    template <class Compare> void merge(List<T, Allocator>& x, Compare comp);
    template <class Compare> void merge(List<T, Allocator>&& x, Compare comp);

    void sort();
    template <class Compare> void sort(Compare comp);

    void reverse() noexcept;
};


#include "List.inl"

}
#endif
