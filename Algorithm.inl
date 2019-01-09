#include <functional>
#include <algorithm>

namespace mystl {

// checks that a predicate is true for all the elements of a sequence
template <class InputIterator, class Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred)
{
  return find_if_not(first, last, pred) == last;
}

template <class InputIterator, class Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred)
{
  return none_of(first, last, pred);
}

template <class InputIterator, class Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate pred)
{
  return find_if(first, last, pred) == last;
}

template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f)
{
	for ( ; first != last; ++first) {
		f(*first);
	}
	return f;
}

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value)
{
	return find_if(first, last, [&value](int i) { return i == value; });
}

template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
{
	for ( ; first != last; ++first) {
		if (pred(*first)) {
			return first;
		}
	}
	return last;
}

template<class InputIterator, class UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	for ( ; first != last; ++first) {
		if (!pred(*first)) {
			return first;
		}
	}
	return last;
}


template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{
	if (first != last) {
		return adjacent_find(first, last, std::equal_to<decltype(*first)>());
	}
	return last;
}

template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
{
	auto next = first;
	++next;
	for ( ; next != last; ++first, ++next) {
		if (pred(*first, *next)) {
			return first;
		}
	}
	return last;
}


template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
									 BidirectionalIterator1 last, BidirectionalIterator2 result)
{

}


namespace {

constexpr std::ptrdiff_t __threshold = 16;

// find the median of three values
template <typename T>
const T& __median(const T& a, const T& b, const T& c)
{
	if (a < b) {
		if (b < c) { return b; } // a < b < c
		else if (a < c) { return c; } // a < c <= b
		else { return a; } // c <= a < b
	} else if (a < c) {
		return a; // b <= a < c
	} else if (b < c) {
		return c; // b < c <= a
	} else {
		return b; // c <= b < a
	}
}

template <typename RandomAccessIterator, typename Compare>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first,
											                     RandomAccessIterator last,
                                           RandomAccessIterator pivot,
                                           Compare comp)
{
	while (true) {

		while (comp(first, pivot)) {
      ++first;
    }
		--last;

		while (comp(last, pivot)) {
      --last;
    }

		if (!(first < last)) {
      return first;
    }
		std::iter_swap(*first, *last);
		++first; // comp(first, pivot) is true
	}
}

template <typename Iterator, typename Compare>
void __move_median_to_first(Iterator result,
                            Iterator a, Iterator b, Iterator c,
                            Compare comp)
{
  if (comp(a, b)) {
    if (comp(b, c)) {
      std::iter_swap(result, b);
    } else if (comp(a, c)) {
      std::iter_swap(result, c);
    } else {
      std::iter_swap(result, a);
    }
  } else if (comp(a, c)) {
    std::iter_swap(result, a);
  } else if (comp(b, c)) {
    std::iter_swap(result, c);
  } else {
    std::iter_swap(result, b);
  }
}

template <typename RandomAccessIterator, typename Compare>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first,
                                           RandomAccessIterator last,
                                           Compare comp)
{
  auto mid = first + (last - first) / 2;
  __move_median_to_first(first, first+1, mid, last-1, comp);
  return __unguarded_partition(first+1, last, first, comp);
}

template <typename RandomAccessIterator, typename Compare>
void __partial_sort(RandomAccessIterator first,
                           RandomAccessIterator middle,
                           RandomAccessIterator last,
                           Compare comp)
{
  __heap_select(first, middle, last, comp);
  __sort_heap(first, middle, comp);
}

template <typename RandomAccessIterator, typename Compare>
void __heap_select(RandomAccessIterator first,
                   RandomAccessIterator middle,
                   RandomAccessIterator last,
                   Compare comp)
{
  __make_heap(first, middle, comp);
  for (RandomAccessIterator i = middle; i < last; ++i) {
    if (comp(i, first)) {
      __pop_heap(first, middle, i, comp);
    }
  }
}

template <typename RandomAccessIterator, typename Compare>
void __pop_heap(RandomAccessIterator first, 
                RandomAccessIterator last,
                RandomAccessIterator result, 
                Compare& comp)
{
  using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
  using DistanceType = typename std::iterator_traits<RandomAccessIterator>::difference_type;

  ValueType value = std::move(*result);
  *result = std::move(*first);
  __adjust_heap(first, DistanceType(0), _DistanceType(last - first), std::move(value), comp);
}

template <typename RandomAccessIterator, typename Compare>
void __sort_heap(RandomAccessIterator first, 
                 RandomAccessIterator last,
                 Compare& comp)
{
  while (last - first > 1) {
    --last;
    __pop_heap(first, last, last, comp);
  }
}

template <typename RandomAccessIterator, typename Size, typename Compare>
void __introsort_loop(RandomAccessIterator first,
					            RandomAccessIterator last,
                      Size depth_limit,
                      Compare comp)
{
	while (last - first > __threshold) {
		if (depth_limit == 0) {
			__partial_sort(first, last, last, comp);
			return ;
		}
		--depth_limit;
		auto cut = __unguarded_partition(first, last, comp);
		__introsort_loop(cut, last, depth_limit, comp);
		last = cut;
	}
}

template <typename Size = size_t>
Size __lg(Size n)
{
	Size k = 0;
	for ( ; n > 1; n >>= 1) { ++k; }
	return k;
}

template <typename RandomAccessIterator, typename T>
void __unguarded_linear_insert(RandomAccessIterator last, T value)
{
	auto next = last - 1;
	while (*next > value) {
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}

template<typename RandomAccessIterator>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last)
{
	for (auto i = first; i != last; ++i) {
		__unguarded_linear_insert(i, (decltype(*first))(*i));
	}
}

template<typename RandomAccessIterator>
void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	__unguarded_insertion_sort_aux(first, last);
}

template<typename RandomAccessIterator>
void __linear_insert(RandomAccessIterator first, RandomAccessIterator last)
{
	auto value = *last;
	if (*first > value) {
		std::copy_backward(first, last, last+1);
		*first = value;
	} else {
		__unguarded_linear_insert(last, value);
	}
}

template<typename RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (first == last) {
		return ;
	}
	for (auto i = first + 1; i != last; ++i) {
		__linear_insert(first, i);
	}
}

template<typename RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (last - first > __threshold) {
		__insertion_sort(first, first + __threshold);
		__unguarded_insertion_sort(first + __threshold, last);
	} else {
		__insertion_sort(first, last);
	}
}

} // unname

template<class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (first != last) {
		__introsort_loop(first, last, __lg(last-first) * 2);
		__final_insertion_sort(first, last);
	}
}

template<class RandomAccessIterator, class Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	
}

template<class ForwardIterator>
bool is_sorted(ForwardIterator first, ForwardIterator last)
{
	return is_sorted_until(first, last) == last;
}

template<class ForwardIterator, class Compare>
bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp)
{
	return is_sorted_until(first, last, comp) == last;
}

template<class ForwardIterator>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last)
{
	return mystl::is_sorted_until(first, last, std::less<decltype(*first)>());
}

template<class ForwardIterator, class Compare>
ForwardIterator is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp)
{
	using namespace std::placeholders;
	auto it = mystl::adjacent_find(first, last, std::bind(comp, _2, _1));
	return it == last ? last : std::next(it);
}

}
