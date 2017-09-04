#include "../Deque.h"

#include <iostream>

using namespace mystl;

template <typename T>
void q(const Deque<T>& d)
{
	for (auto i : d) {
		std::cout << i  << " ";
	}
	std::cout << std::endl;
}

int main()
{
	Deque<int> di(10, 1);
	q(di);
}
