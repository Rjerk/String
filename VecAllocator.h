#ifndef VEC_ALLOCATOR_H
#define VEC_ALLOCATOR_H

namespace mystl {

namespace vector_internal {

template <typename Allocator>
class Storage {
	using size_type = size_t;
	using const_pointer = std::allocator_traits<Allocator>::const_pointer;
	
	Storage(): sz(0), alloacated(0) { }
	Storage(Storage const& rhs) : sz(rhs.sz), allocated(rhs.allocated) { }
	Storage(size_type n, size_type alloc): sz(n), allocated(alloc) { }
	
	void setStorage(size_type n, size_type alloc)
	{
		sz = n;
		allocated = alloc;
	}
	size_type size() const { return sz; }
	size_type allocSize() const { return allocated; }
private:
	size_type sz;
	size_type allocated;
};

}

}

#endif
