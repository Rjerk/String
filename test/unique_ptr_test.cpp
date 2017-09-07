#include "../Unique_ptr.h"

#include <memory>

int main()
{
	using namespace mystl;
	
	Unique_ptr<int> p1(new int(1));
	
	{
		std::unique_ptr<int> p1(new int(1));
		std::unique_ptr<double> p2(new double(1));
		p1 = p2;
	}
}
