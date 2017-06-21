#ifndef LIST_H
#define LIST_H

#include <memory>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace mystl {

namespace list_detail {

template <typename T>

struct Node {


};

class ListIterator: public iterator<bidirectional_iterator_tag,
                                    T,
                                    std::ptrdiff_t,
                                    T*,
                                    T&>
{
public:
    ListIterator();

};

}

template <typename T, typename Allocator = std::allocator<T>>
class List : public Allocator {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const reference;
    using pointer = std::allocator_traits<Allocator>::pointer;
    using pointer = std::allocator_traits<Allocator>::const_pointer;
    using iterator = ListIterator<T>;
    using iterator = ListIterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<iterator>;
private:
    iterator head;
    iterator tail;
public:
    List(): List(Allocator()) { }
    explicit List(const Allocator& alloc);
    List(size_type count, const T& value, const Allocator& alloc = Allocator());
    explicit List(size_type count, const Allocator& alloc = Allocator());
    template <class InputIterator>
        List(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());
    List(const List& rhs);
    List(const List& rhs, const Allocator& alloc);
    List(List&& rhs);
    List(List&& rhs, const Allocator& alloc);
    List(std::initializer_list<T> init, const Allocator& alloc = Allocator());
    ~List();

    List& operator=(const List& rhs);
    List& operator=(List&& rhs);
    List& operator=(std::initializer_list<T>);

    template <class InputIterator>
        void assign(InputIterator first InputIterator last);
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
    template <class... Args> reference emplace_back(Args&&... args);
    void push_front(const T& x);
    void push_front(T&& x);
    void pop_front();
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

    void splice(const_iterator pos, List& x);
    void splice(const_iterator pos, List&& x);
    void splice(const_iterator pos, List& x, const_iterator i);
    void splice(const_iterator pos, List&& x, const_iterator i);
    void splice(const_iterator pos, List& x, const_iterator first, const_iterator last);
    void splice(const_iterator pos, List&& x, const_iterator first, const_iterator last);

    void remove(const T& value);
    template <class Predicate> void remove_if(Predicate pred);

    void unique();
    template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred);

    void merge(List& x);
    void merge(List&& x);

    template <class Compare> void merge(List& x, Compare comp);
    template <class Compare> void merge(List&& x, Compare comp);

    void sort();
    template <class Compare> void sort(Compare comp);

    void reverse() noexcept;
};

template <class T, class Allocator>
bool operator==(const List<T, Allocator>& x, const List<T, Allocator>& y);

template <class T, class Allocator>
bool operator< (const List<T, Allocator>& x, const List<T, Allocator>& y);

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

}

#endif
