#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H

#include <cstddef>

namespace mystl {

struct input_iterator_tag { };

struct output_iterator_tag { };

struct forward_iterator_tag : public input_iterator_tag { };

struct bidirectional_iterator_tag : public forward_iterator_tag { };

struct random_access_iterator_tag : public bidirectional_iterator_tag { };

template<typename Category, typename T, typename Distance = ptrdiff_t,
           typename Pointer = T*, typename Reference = T&>
struct iterator {
      using iterator_category = Category;
      using value_type = T;
      using difference_type = Distance;
      using pointer = Pointer;
      using reference = Reference;
};

template <typename Iterator>
struct iterator_traits {
	using iterator_category = typename Iterator::iterator_category;
	using value_type = typename Iterator::value_type;
	using difference_type = typename Iterator::difference_type;
	using pointer = typename Iterator::pointer;
	using reference = typename Iterator::reference;
};

template <typename T>
struct iterator_traits<T*> {
	using iterator_category = random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;
};

template <typename T>
struct iterator_traits<const T*> {
	using iterator_category = random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = const T*;
	using reference = const T&;
};

template <typename InputIterator, class Distance>
    void advance(InputIterator& i, Distance n);
template <typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last);
template <typename ForwardIterator>
    ForwardIterator next(ForwardIterator x,
        typename iterator_traits<ForwardIterator>::difference_type n = 1);
template <typename BidirectionalIterator>
    BidirectionalIterator prev(BidirectionalIterator x,
        typename iterator_traits<BidirectionalIterator>::difference_type n = 1);

template <typename Iterator>
class reverse_iterator: public iterator<typename iterator_traits<Iterator>::iterator_category,
										typename iterator_traits<Iterator>::value_type,
										typename iterator_traits<Iterator>::difference_type,
										typename iterator_traits<Iterator>::pointer,
										typename iterator_traits<Iterator>::reference>
{
public:
	using iterator_type =  Iterator;
	using difference_type = typename iterator_traits<Iterator>::difference_type;
	using reference = typename iterator_traits<Iterator>::reference;
	using pointer = typename iterator_traits<Iterator>::pointer;

	reverse_iterator(): current() { }
	explicit reverse_iterator(Iterator x);
	template <class U> reverse_iterator(const reverse_iterator<U>& u);
	template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u);
	Iterator base() const
	{
		return current; 
	}
	reference operator*() const
	{
		Iterator tmp = current;
		return *--tmp;
	}
	pointer operator->() const
	{
		return addressof(operator*());
	}
	reverse_iterator& operator++()
	{
		--current;
		return *this;
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--current;
		return tmp;
	}
	reverse_iterator& operator--()
	{
		++current;
		return *this;
	}
	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		++current;
		return tmp;
	}
	reverse_iterator operator+ (difference_type n) const
	{
		return reverse_iterator(current-n);
	}
	reverse_iterator& operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}
	reverse_iterator operator- (difference_type n) const
	{
		return reverse_iterator(current+n);
	}
	reverse_iterator& operator-=(difference_type n)
	{
		current += n;
		return *this;
	}
//	typename Iterator::value_type operator[](difference_type n) const
//	{
//		return current[-n-1];
//	}

protected:
	Iterator current;
};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current == y.current;
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current > y.current;
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current != y.current;
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current < y.current;
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current <= y.current;
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
{
	return x.current >= y.current;
}

template <class Iterator1, class Iterator2>
auto operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
		-> decltype(y.base() - x.base())
{
	return y.current - x.current;
}

template <class Iterator>
reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n,
									const reverse_iterator<Iterator>& x)
{
	return reverse_iterator<Iterator>(x.current - n);
}

template <class Iterator>
reverse_iterator<Iterator> make_reverse_iterator(Iterator i)
{
	return reverse_iterator<Iterator>(i);
}




// inserter
template <typename Container>
class back_insert_iterator: public iterator<output_iterator_tag, void, void, void, void> {
public:
	using container_type = Container;
	explicit back_insert_iterator(Container& x) : container(addressof(x)) {	}
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value)
	{
		container->push_back(value);
		return *this;
	}
	back_insert_iterator<Container>& operator=(typename Container::value_type&& value)
	{
		container->push_back(std::move(value));
		return *this;
	}
	back_insert_iterator<Container>& operator*()
	{
		return *this;
	}
	back_insert_iterator<Container>& operator++()
	{
		
		return *this;
	}
	back_insert_iterator<Container> operator++(int)
	{
		
		return *this;
	}
protected:
	Container* container;
};

template <typename Container>
back_insert_iterator<Container> back_inserted(Container& x)
{
	return back_inserter_iterator<Container>(x);
}

template <typename Container>
class front_insert_iterator: public interator<output_iterator_tag, void, void, void, void> {
public:
	using container_type = Container;
	explicit front_insert_iterator(Container& x): container(addressof(x)) {	}
	front_insert_iterator<Container>& operator=(const typename Container::value_type& value)
	{
		container->push_front(value);
	}
	front_insert_iterator<Container>& operator=(typename Container::value_type&& value)
	{
		container->push_front(std::move(value));
	}
	front_insert_iterator<Container>& operator*()
	{
		// todo
		return *this;
	}
	front_insert_iterator<Container>& operator++()
	{
		// todo
		return *this;
	}
	front_insert_iterator<Container> operator++(int)
	{
		// todo
		return *this;
	}
protected:
	Container* container;
};

template <typename Container>
front_insert_iterator<Container> front_inserter(Container& x)
{
	return front_insert_iterator<Container>(x);
}

template <typename Container>
class insert_iterator: public interator<output_iterator_tag, void, void, void, void> {
public:
	using container_type = Container;
	explicit insert_iterator(Container& x, typename Container::iterator i)
		: container(addressof(x)), iter(i) { }
	insert_iterator<Container>& operator=(const typename Container::value_type& value)
	{
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}
	insert_iterator<Container>& operator=(typename Container::value_type&& value)
	{
		iter = container->insert(iter, std::move(value));
		++iter;
		return *this;
	}
	insert_iterator<Container>& operator*()
	{
		// todo
		return *this;
	}
	insert_iterator<Container>& operator++()
	{
		// todo
		return *this;
	}
	insert_iterator<Container> operator++(int)
	{
		// todo
		return *this;
	}
protected:
	Container* container;
	typename Container::iterator iter;
};

template <typename Container>
insert_iterator<Container> inserter(Container& x, typename Container::iterator i)
{
	return front_insert_iterator<Container>(x, i);
}

template <typename Iterator>
class move_iterator {

};





template <typename C>
auto begin(C& c) -> decltype(c.begin())
{
	return c.begin();
}

template <typename C>
auto begin(const C& c) -> decltype(c.begin())
{
	
}

template <typename C>
auto end(C& c) -> decltype(c.end())
{
	
}

template <typename C>
auto end(const C& c) -> decltype(c.end())
{
	
}

template <class T, size_t N>
constexpr T* begin(T (&array)[N]) noexcept
{
	
}

template <class T, size_t N>
constexpr T* end(T (&array)[N]) noexcept
{
	
}

template <class C>
constexpr auto cbegin(const C& c) noexcept(noexcept(std::begin(c)))
	-> decltype(std::begin(c))
{
	
}

template <class C>
constexpr auto cend(const C& c) noexcept(noexcept(std::end(c)))
	-> decltype(std::end(c))
{
	
}

template <class C>
auto rbegin(C& c) -> decltype(c.rbegin())
{
	
}

template <class C>
auto rbegin(const C& c) -> decltype(c.rbegin())
{
	
}

template <class C>
auto rend(C& c) -> decltype(c.rend())
{
	
}

template <class C>
auto rend(const C& c) -> decltype(c.rend())
{
	
}

template <class T, size_t N>
reverse_iterator<T*> rbegin(T (&array)[N])
{
	
}

template <class T, size_t N>
reverse_iterator<T*> rend(T (&array)[N])
{
	
}

template <class E>
reverse_iterator<const E*> rbegin(initializer_list<E> il)
{
	
}

template <class E>
reverse_iterator<const E*> rend(initializer_list<E> il)
{
	
}

template <class C>
auto crbegin(const C& c) -> decltype(std::rbegin(c))
{
	
}

template <class C>
auto crend(const C& c) -> decltype(std::rend(c))
{
	
}




}

#endif
