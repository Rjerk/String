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
struct Iterator {
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
class reverse_iterator;

template <typename Iterator1, typename Iterator2>
bool operator==(const reverse_iterator<Iterator1>& x,
                const reverse_iterator<Iterator2>& y);




template <typename C>
auto begin(C& c) -> decltype(c.begin());

}

#endif
