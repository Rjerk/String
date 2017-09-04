#include "../List.h"

#include "../String.h"
#include "../Vector.h"
#include <list>
#include <cassert>

using namespace mystl;
using std::cout;
using std::endl;

template <typename T>
void q(const List<T>& l)
{
	for (auto e : l) {
		cout << e << " ";
	}
	cout << endl;
	cout << "size: " << l.size() << endl;
}

int main()
{
	{
		cout << "constructor test.\n";
		List<int> l1;
		q(l1);
		
		List<int> l2(5);
		q(l2);
		
		List<int> l3(4, 4);
		q(l3);
		
		Vector<int> vi{1, 2, 3};
		List<int> l4(vi.cbegin(), vi.cend());
		q(l4);
		
		List<int> l5(l3);
		q(l5);
		
		List<int> l6(List<int>(3));
		q(l6);
		
		List<int> l7 {1, 2, 3, 4};
		q(l7);
	}
	{
		cout << "\noperator= test.\n";
		List<String> tmp{"123", "345"};
		List<String> ls1 = tmp;
		q(ls1);
		
		List<String> ls2 = List<String>({"234", "890"});
		q(ls2);
	}
	{
		cout << "\nassign test.\n";
		List<int> tmp{1, 2, 3, 4};
		List<int> li1;
		li1.assign(tmp.cbegin(), tmp.cend());
		q(li1);
		
		li1.assign(4, 9);
		q(li1);
		
		li1.assign({2, 3, 4});
		q(li1);
	}
	{
		cout << "\naresize test.\n";
		List<int> li1{1, 2, 3};
		li1.resize(10, 1);
		q(li1);
		li1.resize(5);
		q(li1);
	}
	{
		cout << "\nafront/back/emplace_front/emplace_back/pop_front/pop_back/push_front/push_back test.\n";
		List<int> li{1, 2, 3};
		q(li);
		cout << "front: " << li.front() << " back: " << li.back() << "\n";
		li.emplace_front(0);
		li.emplace_back(4);
		q(li);
		cout << "front: " << li.front() << " back: " << li.back() << "\n";
		li.pop_front();
		li.pop_back();
		q(li);
		cout << "front: " << li.front() << " back: " << li.back() << "\n";
		li.push_front(0);
		li.push_back(4);
		q(li);
		cout << "front: " << li.front() << " back: " << li.back() << "\n";
	}
	{
		cout << "\nemplace/insert/erase test.\n";
		List<int> li{1, 2, 3, 4};
		li.emplace(li.begin(), 0);
		q(li);
		
		int a = 10;
		li.insert(li.cbegin(), a);
		li.insert(li.cbegin(), 9);
		q(li);
		
		li.insert(li.cbegin(), 3, 1);
		q(li);
		
		Vector<int> vi(3, 2);
		li.insert(li.cend(), vi.cbegin(), vi.cend());
		q(li);
		
		li.insert(li.cend(), {5, 6, 7});
		q(li);
		
		li.erase(++li.cbegin());
		q(li);
		
		li.erase(li.cbegin(), --li.cend());
		q(li);
	}
	{
		cout << "\nswap/clear test.\n";
		List<int> tmp{1, 2, 3};
		List<int> li;
		li.swap(tmp);
		q(li);
		q(tmp);
		li.clear();
		q(li);
	}
	{
		cout << "\nsplice test.\n";
		List<int> tmp{1, 2, 3};
		List<int> li{0, 4, 5};
		li.splice(++li.cbegin(), tmp); // undo: change size().
		q(li);
		q(tmp);
		
		tmp.assign({-2, -1});
		q(tmp);
		li.splice(li.cbegin(), tmp, tmp.cbegin());
		q(li);
		q(tmp);
	}
	{
		cout << "\nmerge test.\n";
		List<int> l1{1, 2, 3};
		List<int> l2{5, 6, 7};
		l1.merge(l2);
		q(l1);
		q(l2);
	}
}
