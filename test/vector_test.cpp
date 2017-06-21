#include "my_vector.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

using namespace mystl;

void q(const Vector<int>& v) { cout << v << "\n"; }

int main()
{
	{
		cout << "constructor:\n";
		Vector<int> v1;
		cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << "\n";

		Vector<int> v2(10, 4);
		q(v2);

		Vector<int> v3(10);
		q(v3);
		
		Vector<int> v4(v2);
		q(v4);
		
		Vector<int> v5(std::move(Vector<int>(3, 5)));
		q(v5);
		
		Vector<int> v6({1, 2, 3, 4});
		q(v6);
		
		v5 = v6;
		q(v5);
	}
	{
		cout << "\nswap:\n";
		Vector<int> a(4, 3);
		Vector<int> b(2, 1);
		cout << "first swap:\n";
		mystl::swap(a, b);
		cout << "a:";
		q(a);
		cout << "b:";
		q(b);		
		cout << "second swap:\n";
		a.swap(b);
		cout << "a:";
		q(a);
		cout << "b:";
		q(b);
	}
	{
		cout << "\nassign:\n";
		Vector<int> v1;
		v1.assign(3, 4);
		q(v1);

		Vector<int> v2;
		v2.assign({1, 2, 3, 4});
		q(v2);
	}
	{
		cout << "\nat\n";
		Vector<int> v = {1, 2, 3, 4, 5};
		cout << v.at(1) << "\n";
		v.at(1) = 10;
		q(v);
	}
	{
		cout << "\noperator[]\n";
		Vector<int> v = {1, 2, 3, 4, 5};
		cout << v[1] << "\n";
		v[1] = 11;
		q(v);
	}
	{
		cout << "\nfront\\back\n";
		Vector<int> v = {1, 3, 5, 7, 9};
		cout << v.front() << "\n";
		v.front() = 10;
		cout << v.back() << "\n";
		v.back() = 100;
		q(v);
	}
	{
		cout << "\ndata\n";
		Vector<int> v = {1, 3, 5, 7, 9};
		Vector<int>::const_pointer data = v.data();
		cout << *data << "\n";
		// *data = 10; // error.
		Vector<int>::pointer data2 = v.data();
		*data2 = 11;
		q(v);
	}
	{
		cout << "\nbegin()\n";
		Vector<int> v = {1, 3, 5, 7, 9};
		for (Vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter)
			*iter = 0;
		q(v);
		for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
			cout << *iter << " ";
	}
	{
		cout << "\n\nreserve\\resize\\shink_to_fit\\clear\n";
		Vector<int> v;
		cout << v.size() << " " << v.capacity() << "\n";
		v.reserve(10);
		cout << v.size() << " " << v.capacity() << "\n";
		v.assign({1, 2, 3, 4, 5});
		cout << v.size() << " " << v.capacity() << "\n";
		q(v);
//		v.resize(3);
//		cout << v.size() << " " << v.capacity() << "\n";
//		q(v);
		v.shrink_to_fit();
		cout << v.size() << " " << v.capacity() << "\n";
		q(v);
		v.clear();
		cout << v.size() << " " << v.capacity() << "\n";
		q(v);
	}
	{
		cout << "\ninsert\n";
		Vector<int> v;
		v.reserve(10);
		v.assign({1, 2, 3});
		int a = 10;
		cout << v.size() << " " << v.capacity() << "\n";
		v.insert(v.begin(), 1);
		cout << v.size() << " " << v.capacity() << "\n";
		q(v);
		v.insert(v.end()-1, 10, 4);
		q(v);
	}
	{
		cout << "\nerase\n";
		Vector<int> v = {1, 3, 5, 7, 9};
		v.erase(v.begin()+1);
		q(v);
		v.erase(v.begin(), v.end());
		cout << v.size() << endl;
	}
	{
		cout << "\n\n";
	}
}
