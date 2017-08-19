#include <new>
#include <iostream>
#include <limits>

#include "Memory.h"
#include "Iterator.h"

namespace mystl {

namespace {

template <typename T>
inline T* _allocate(std::ptrdiff_t size, T*)
{
    std::set_new_handler(0);
    T* tmp = nullptr;
    try {
        tmp = (T*)(::operator new(static_cast<size_t>(size * sizeof(T))));
    } catch (std::bad_alloc& ba) {
        std::cerr << "out of memory" << std::endl;
        exit(1);
    }
    return tmp;
}

template <typename T>
inline void _deallocate(T* buffer)
{
    ::operator delete(buffer);
}

template <typename T1, typename T2>
inline void _construct(T1* p, const T2& value)
{
    ::new (p) T1(value);
}

template <typename T>
inline void _destroy(T* ptr)
{
    ptr->~T();
}

}

template <typename T>
typename Allocator<T>::pointer
Allocator<T>::address(reference x) const noexcept
{
    return static_cast<pointer>(&x);
}

template <typename T>
typename Allocator<T>::const_pointer
Allocator<T>::address(const_reference x) const noexcept
{
    return static_cast<const_pointer>(&x);
}

template <typename T>
typename Allocator<T>::pointer
Allocator<T>::allocate(size_type n, Allocator<void>::const_pointer hint)
{
    (void) hint;
    return _allocate(static_cast<difference_type>(n), static_cast<pointer>(0));
}

template <typename T>
void Allocator<T>::deallocate(pointer p, size_type n)
{
    (void) n;
    delete _deallocate(p);
}

template <typename T>
template <class U, class... Args>
void Allocator<T>::construct(U* p, Args&&... args)
{
    ::new ((void *)p) U(std::forward<Args>(args)...);
}

template <typename T>
template <class U>
void Allocator<T>::destroy(U* p)
{
    p->~U();
}

template <typename T>
typename Allocator<T>::size_type
Allocator<T>::max_size() const noexcept
{
    return std::numeric_limits<size_type>::max();
}

template <typename T, typename U>
bool operator==(const Allocator<T>& , const Allocator<T>& ) noexcept
{
    return true;
}

template <typename T, typename U>
bool operator!=(const Allocator<T>& , const Allocator<T>& ) noexcept
{
    return false;
}

template <typename T>
T* addressof(T& value) noexcept
{
    return reinterpret_cast<T*>(
                &const_cast<char&>(reinterpret_cast<const volatile char&>(value)));
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	for (; first != last; ++result, ++first) {
        ::new (static_cast<void*>(&*result))
                typename iterator_traits<ForwardIterator>::value_type(*first);
    }
	return result;
}

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
{
	for ( ; n > 0; ++result, ++first, --n) {
        ::new (static_cast<void*>(&*result))
                typename iterator_traits<ForwardIterator>::value_type(*first);
    }
	return result;
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x)
{
	for (; first != last; ++first) {
        ::new (static_cast<void*>(&*first))
                typename iterator_traits<ForwardIterator>::value_type(x);
    }
}

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
{
	for (; n--; ++first) {
        ::new (static_cast<void*>(&*first))
		        typename iterator_traits<ForwardIterator>::value_type(x);
    }
	return first;
}

}
