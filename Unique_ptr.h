#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <tuple>

namespace mystl {

template <typename T>
struct default_delete {
	constexpr default_delete() noexcept = default; // constexpr used in a function declaration implies inline.
	template <typename U> default_delete(const default_delete<U>&);
	void operator()(T* ptr) const;
};

template <typename T>
struct default_delete<T[]> {
	constexpr default_delete() noexcept = default;
	void operator()(T* ptr) const;
	template <U> void operator(U*) const = delete;
};

template <typename T, typename Deleter = default_delete<T>>
class Unique_ptr {
	class Pointer {
		// use SFINAE to test whether Del::pointer exists.
		template <typename U>
		static typename U::pointer test(typename U::pointer*);
		
		template <typename U>
		static T* test(...);

		using Del = typename std::remove_reference<Deleter>::type;

	public:
		using type = decltype(test<Del>(0));
	};
	
	using tuple_type = std::tuple<typename Pointer::type, Deleter>;
	tuple_type ptr_;
public:
	using element_type = T;
	using pointer = T*;
	using deleter_type = Deleter;

	constexpr Unique_ptr() noexcept;
	constexpr Unique_ptr(nullptr_t) noexcept;
	explicit Unique_ptr(pointer ptr) noexcept;
	Unique_ptr(Unique_ptr&& u) noexcept;
	template<typename U, typename E> Unique_ptr(Unique_ptr<U, E>&& u ) noexcept;

	~Unique_ptr();
	
	Unique_ptr& operator=(Unique_ptr&& r ) noexcept;
	template<typename U, typename E> Unique_ptr& operator=(Unique_ptr<U, E>&& r) noexcept;
	Unique_ptr& operator=(nullptr_t) noexcept;

	pointer release() noexcept;

	void reset(pointer ptr = pointer()) noexcept;

	void swap(Unique_ptr& other) noexcept;

	pointer get() const noexcept; // return dump pointer.

	deleter_type& get_deleter() noexcept;
	const deleter_type& get_deleter() const noexcept;

	explicit operator bool() const noexcept;
	
	typename std::add_lvalue_reference<T>::type operator*() const;
	pointer operator->() const noexcept;
	
	T& operator[](size_t i) const;
	
	template<typename T, typename Deleter >
	void swap(Unique_ptr<T,Deleter>& lhs, Unique_ptr<T, Deleter>& rhs ) noexcept;
	
	Unique_ptr(const Unique_ptr&) = delete;
	Unique_ptr& operator=(const Unique_ptr&) = delete;
};

template<typename T, typename... Args >
Unique_ptr<T> make_unique(Args&&... args); // for non-array types.

template <typename T, typename D>
void swap(Unique_ptr<T, D>& x, Unique_ptr<T, D>& y) noexcept;

}

#include "Unique_ptr.inl"

#endif 
