#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>

namespace mystl {

template <typename Ptr>
struct pointer_traits {
    using pointer = Ptr;
    using elements_type = typename Ptr::elements_type;
    using difference_type = ptrdiff_t;
    //template <class U> using rebind = Ptr::rebind<U>;
    static pointer pointer_to();
};

template <typename T>
struct pointer_traits<T*> {
    using pointer = T*;
    using elements_type = T;
    using difference_type = ptrdiff_t;
    template <class U> using rebind = U*;
    static pointer pointer_to() noexcept;
};

template <typename T>
class Allocator;

template <>
class Allocator<void> {
public:
    using value_type = void;
    using pointer = void*;
    using const_pointer = const void*;
    template <class U> struct rebind { using other = Allocator<U>; };
};

template <typename T>
class Allocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    template <class U> struct rebind { using other = Allocator<U>; };

    Allocator() noexcept = default;
    Allocator(const Allocator& rhs) noexcept = default;
    ~Allocator() = default;

    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    pointer allocate(size_type n, Allocator<void>::const_pointer hint = 0);
    void deallocate(pointer p, size_type n);

    template <class U, class... Args>
        void construct(U* p, Args&&... args);

    template <class U>
        void destroy(U* p);

    size_type max_size() const noexcept;
};

template <typename T, typename U>
bool operator==(const Allocator<T>& , const Allocator<T>& ) noexcept;

template <typename T, typename U>
bool operator!=(const Allocator<T>& , const Allocator<T>& ) noexcept;

template <typename T>
T* addressof(T& value) noexcept;

template <typename T>
const T* addressof(const T&& value) = delete;

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result);

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result);

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x);

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x);

}

#include "Memory.inl"

#endif
