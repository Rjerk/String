#include "../Algorithm.h"
#include "../Vector.h"

#include <iostream>
#include <cassert>

using namespace mystl;

template <typename T>
void q(const Vector<T>& v)
{
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main()
{
	{ // all_of
		Vector<int> vi{1, 2, 3, 4};
		assert(mystl::all_of(vi.cbegin(), vi.cend(), [](int i) { return i > 0 && i <= 4; }));
	}
	{ // any_of
		Vector<int> vi{1, 2, 3, 4};
		assert(mystl::any_of(vi.cbegin(), vi.cend(), [](int i) { return i == 3; }));
	}
	{ // none_of
		Vector<int> vi{1, 2, 3, 4};
		assert(mystl::none_of(vi.cbegin(), vi.cend(), [](int i) { return i > 4; }));
	}
	{ // for_each
		Vector<int> vi{1, 2, 3, 4};
		mystl::for_each(vi.begin(), vi.end(), [](int& i) { i *= 2; });
		//q(vi);
	}
	{ // find
		Vector<int> vi{1, 2, 3, 4};
		assert(mystl::find(vi.cbegin(), vi.cend(), 3) != vi.cend());
		assert(mystl::find_if(vi.cbegin(), vi.cend(), [](int i) { return i % 5 == 0; }) == vi.cend());
		assert(mystl::find_if_not(vi.cbegin(), vi.cend(), [](int i) { return i % 5 != 0; }) == vi.cend());
	}
	{ // adjacent_find
		Vector<int> vi{1, 2, 2, 4};
		assert(mystl::adjacent_find(vi.cbegin(), vi.cend()) == vi.cbegin()+1);
		assert(mystl::adjacent_find(vi.cbegin(), vi.cend(), [](int i, int j){ return i > j; }) == vi.cend());
	}
	{ // sort
		Vector<int> vi{5, -1, 0, 2};
		mystl::sort(vi.begin(), vi.end());
		q(vi);
	}
	{ // is_sorted + is_sorted_until
		Vector<int> vi{1, 2, 3, -1};
		assert(mystl::is_sorted(vi.cbegin(), vi.cend()) == false);
		assert(mystl::is_sorted_until(vi.cbegin(), vi.cend()) == vi.cend()-1);
	}
}
