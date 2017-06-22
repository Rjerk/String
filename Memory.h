#ifndef MEMORY_H
#define MEMORY_H

namespace mystl {

template <typename T>
T* addressof(T& value) noexcept
{
    return reinterpret_cast<T*>(
                &const_cast<char&>(
                    reinterpret_cast<const volatile char&>(value)));
}

template <typename T>
const T* addressof(const T&& value) = delete;

template <typename Ptr>
struct pointer_traits {
    using pointer = Ptr;
    using elements_type = Ptr::elements_type;
    using difference_type = ptrdiff_t;

    template <class U>
        using rebind = ;
    static pointer pointer_to();
};

template <typename T>
struct pointer_traits<T*> {
    using pointer = T*;
    using elements_type = T;
    using difference_type = ptrdiff_t;

    template <class U>
        using rebind = U*;

    static pointer pointer_to() noexcept;
};

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	for (; first != last; ++result, ++first)
		::new (static_cast<void*>(&*result))
				typename iterator_traits<ForwardIterator>::value_type(*first);
	return result;
}

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
{
	for ( ; n > 0; ++result, ++first, --n)
		::new (static_cast<void*>(&*result))
				typename iterator_traits<ForwardIterator>::value_type(*first);
	return result;
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x)
{
	for (; first != last; ++first)
		::new (static_cast<void*>(&*first))
				typename iterator_traits<ForwardIterator>::value_type(x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
{
	for (; n--; ++first)
		::new (static_cast<void*>(&*first))
				typename iterator_traits<ForwardIterator>::value_type(x);
	return first;
}









}












}

#endif
