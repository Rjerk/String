#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <memory>
#include <stdexcept>
#include <new> // bad_alloc

namespace mystl {

constexpr size_t MIN_ALLIGNMENT = 16;

template <typename T>
class Allcator;

template <>
class Allocator<void> {
public:
    using value_type = void;
    using pointer = void*;
    using const_pointer = const void*;

    template <class U>
		struct rebind { using other = Allocator<U>; }
};

template <typename T>
class Allocator {
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    template <class U> struct rebind() { using other = Allocator<U>; }
    using propagate_on_container_move_assignment = std::true_type;

    Allocator() noexcept { }
    Allocator(const Allocator& rhs) noexcept { }
    template <class U>
	    Allocator(const Allocator<U>& rhs) noexcept
	{
		return *this;
	}
    ~Allocator() { }

    pointer address(reference x) const noexcept
    {
    	
	}
    const_pointer address(const_reference x) const noexcept
    {
        return addressof(x);
    }

    pointer allocate(size_type n, Allocator<void>::const_pointer hint = 0)
    {
    	::new (MIN_ALIGNMENT,)
    	pointer storage = nullptr;
    	try {
    		storage = ::new T[n];
		} catch (std::bad_alloc) {
			delete [] storage;
		}
	}
	void deallocate(pointer p, size_type n)
	{
		delete [] storage;
	}

    template <class U, class... Args>
        void construct(U* p, Args&&... args)
    {
        ::new ((void *)p) U(std::forward<Args>(args)...);
    }
    template <class U>
        void destruct(U* p)
    {
        p->~U();
    }
    size_type max_size() const noexcept
    {
    	//return std::numeric_limits<size_type>::max();
	}
};

template <typename T, typename U>
bool operator==(const Allocator<T>& lhs, const Allocator<T>& rhs) noexcept
{
	return true;
}

template <typename T, typename U>
bool operator!=(const Allocator<T>& lhs, const Allocator<T>& rhs) noexcept
{
	return false;
}

}

#endif
