#include "Iterator.h"

namespace mystl {

template <typename T>
template <typename U, typename = RequireConvertible<U*, T*>>
default_delete<T>::default_delete(const default_delete<U>&)
{
}

template <typename T>
void default_delete<T>::operator()(T* ptr) const
{
	static_cast(sizeof(T) > 0, "Can't delete pointer to incomplete type");
	delete ptr;
}

template <typename T>
void default_delete<T[]>::operator()(T* ptr) const
{
	static_cast(sizeof(T) > 0, "Can't delete pointer to incomplete type");
	delete [] ptr;
}



template<typename T, typename Deleter>
Unique_ptr<T>::Unique_ptr()
	: ptr_() 
{
}

template<typename T, typename Deleter>
constexpr Unique_ptr<T>::Unique_ptr(nullptr_t) noexcept;

template<typename T, typename Deleter>
Unique_ptr<T>::Unique_ptr(pointer ptr) noexcept;

template<typename T, typename Deleter>
Unique_ptr<T>::Unique_ptr(Unique_ptr&& u) noexcept;

template<typename T, typename Deleter>
template<typename U, typename E>
Unique_ptr<T>::Unique_ptr(Unique_ptr<U, E>&& u) noexcept;

template<typename T, typename Deleter>
Unique_ptr<T>::~Unique_ptr();

template<typename T, typename Deleter>
Unique_ptr& Unique_ptr<T>::operator=(Unique_ptr&& r ) noexcept;

template<typename T, typename Deleter>
template<typename U, typename E>
Unique_ptr& Unique_ptr<T>::operator=(Unique_ptr<U, E>&& r) noexcept;

template<typename T, typename Deleter>
Unique_ptr& Unique_ptr<T>::operator=(nullptr_t) noexcept;

template<typename T, typename Deleter>
typename Unique_ptr<T>::pointer
Unique_ptr<T>::release() noexcept;

template<typename T, typename Deleter>
void Unique_ptr<T>::reset(pointer ptr = pointer()) noexcept;

template<typename T, typename Deleter>
void Unique_ptr<T>::swap(Unique_ptr& other) noexcept;

template<typename T, typename Deleter>
typename pointer Unique_ptr<T>::get() const noexcept; // return dump pointer.

template<typename T, typename Deleter>
typename deleter_type& Unique_ptr<T>::get_deleter() noexcept;

template<typename T, typename Deleter>
const deleter_type& Unique_ptr<T>::get_deleter() const noexcept;

template<typename T, typename Deleter>
Unique_ptr<T>::operator bool() const noexcept;

template<typename T, typename Deleter>
typename std::add_lvalue_reference<T>::type Unique_ptr<T>::operator*() const;

template<typename T, typename Deleter>
typename pointer Unique_ptr<T>::operator->() const noexcept;

template<typename T, typename Deleter>
T& Unique_ptr<T>::operator[](size_t i) const;

template<typename T, typename Deleter>
void Unique_ptr<T>::swap(Unique_ptr<T, Deleter>& lhs, Unique_ptr<T, Deleter>& rhs ) noexcept;


// non-member functions

template<typename T, typename... Args >
Unique_ptr<T> make_unique(Args&&... args)
{
	return Unique_ptr<T>(new T(std::forward<Args>(args)...));
}



template<typename T, typename D>
void swap(Unique_ptr<T, D>& x, Unique_ptr<T, D>& y) noexcept
{
	
}

}
