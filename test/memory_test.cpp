#include "../Memory.h"
#include <iostream>

template <typename T>
struct Ptr {
    T* pad;
    T* data;
    Ptr(T* arg): pad(nullptr), data(arg)
    {
        std::cout << "Ctor this = " << this << std::endl;
    }
    ~Ptr() { delete data; }
    T** operator&() { return &data; }
};

template <typename T>
void f(Ptr<T>* p)
{
    std::cout << "Ptr overload called with p = " << p << "\n";
}

void f(int** p)
{
    std::cout << "int** overload called with p = " << p << "\n";
}

int main()
{
//    Ptr<int> p(new int(35));
//    f(&p);
//    f(mystl::addressof(p));
	
}
