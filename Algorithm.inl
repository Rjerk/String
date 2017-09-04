#include <functional>
#include <algorithm>

namespace mystl {

template <class InputIterator, class Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred)
{
	if (first != last) {
		while (first != last) {
			if (!pred(*first++)) {
				return false;
			}
		}
	}
	return true;
}

template <class InputIterator, class Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred)
{
	if (first != last) {
		while (first != last) {
			if (pred(*first++)) {
				return true;
			}
		}
	}
	return false;
}

template <class InputIterator, class Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate pred)
{
	if (first != last) {
		while (first != last) {
			if (pred(*first++)) {
				return false;
			}
		}
	}
	return true;
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

template<class InputIterator, class Predicate>
InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred)
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
		return mystl::adjacent_find(first, last, std::equal_to<decltype(*first)>());
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





namespace {

constexpr std::ptrdiff_t __threshold = 16;
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

template <typename RandomAccessIterator, typename T>
RandomAccessIterator __unguarded_partition( RandomAccessIterator first,
											RandomAccessIterator last, const T& pivot)
{
	for ( ; ; ) {
		while (*first < pivot) { ++first; }
		--last;
		while (*last > pivot) {	--last;	}
		if (!(first < last)) { return first; }
		std::swap(*first, *last);
		++first;
	}
}

template <typename RandomAccessIterator, typename Size>
void __introsort_loop(RandomAccessIterator first,
					  RandomAccessIterator last, Size depth_limit)
{
	while (last - first > __threshold) {
		if (depth_limit == 0) {
			std::partial_sort(first, last, last);
			return ;
		}
		--depth_limit;
		auto cut = __unguarded_partition(first, last, __median(*first, *(first + (last - first) / 2), *(last - 1)));
		__introsort_loop(cut, last, depth_limit);
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
	return mystl::is_sorted_until(first, last) == last;
}

template<class ForwardIterator, class Compare>
bool is_sorted(ForwardIterator first, ForwardIterator last, Compare comp)
{
	return mystl::is_sorted_until(first, last, comp) == last;
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
