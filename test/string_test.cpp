#include "../String.h"
#include <ios>

int main()
{
	{
		String s;
		cout << s << "\n\n"; // null

		String s1("1234567890");
		cout << s1 << "\n\n"; // 123456790

		String s2(s1);
		cout << s2 << "\n\n"; // 123456790

		String s3 = s1;
		cout << s3 << "\n\n"; // 123456790

		String bemoved1("123321123");
		String s4 = std::move(bemoved1);
		cout << s4 << "\n\n"; // 123321123

		String bemoved2("123123123");
		String s5(std::move(bemoved2));
		cout << s5 << "\n\n"; // 123123123

		String s6(s1, 1, 4);
		cout << s6 << "\n\n"; // 2345

		//String s7(s1, 10, 4); // out_of_range error
		//cout << s7 << "\n\n";

		String s8(s1, 3);
		cout << s8 << "\n\n"; // 4567890

		String s9("1234567890", 3);
		cout << s9 << "\n\n"; // 123

		String s10(3, 'c');
		cout << s10 << "\n\n"; // ccc

		String s11(s1.begin(), s1.end());
		cout << s11 << "\n\n"; // 1234567890

		String s12({'1', '2', '3', 'a', 'b'});
		cout << s12 << "\n\n"; // 123ab
	}
	{
		String s("abcde");
		cout << s << endl; // abcde
		cout << "front(): " << s.front() << endl; // a
		cout << "back(): " << s.back() << endl; // e
		cout << "c_str(): " << s.c_str() << endl; // abcde
		cout << "empty(): " << std::boolalpha << s.empty() << endl; // false
		cout << "length(): " << s.length() << endl; // 5
		cout << "size(): " << s.size() << endl; // 5
		cout << "at(2): " << s.at(2) << endl; // c
		cout << "data(): " << s.data() << endl; // abcde
		cout << "maxsize(): " << s.max_size() << endl; // 4294967294
		cout << "npos: " << s.npos << "\n\n"; // 4294967295
	}
	{
		String s;
		cout << s.size() << " " << s.capacity() << endl; // 0 0
		s = 'c';
		cout << s.size() << " " << s.capacity() << endl; // 1 1
		String s1("1234");
		cout << s1.size() << " " << s1.capacity() << endl; // 4 4
		s1 = 'a';
		cout << s1.size() << " " << s1.capacity() << endl; // 1 4
		String s2("2345");
		s = s2;
		cout << s << " " << s.size() << " " << s.capacity() << endl; // 2345 4 4
		s = "12345";
		cout << s << " " << s.size() << " " << s.capacity() << endl; // 12345 5 8
		s = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
		cout << s << " " << s.size() << " " << s.capacity() << "\n\n"; // abcdefghi 9 13
	}
	{
		String s("1234567890000");
		cout << s << endl; // 1234567890000
		cout << "capacity(): " << s.capacity() << endl; // 13
		s.reserve(20);
		cout << "capacity(): " << s.capacity() << endl; // 26
		s.resize(15);
		cout << s << endl; // 1234567890000
		cout << "capacity(): " << s.capacity() << endl; // 26
		s.resize(20, 'c');
		cout << s << endl; // 1234567890000  ccccc
		s.clear();
		cout << s << endl; // null
		cout << "size():" << s.size() << endl; // 0
		cout << "capacity(): " << s.capacity() << endl; // 26
		s.shrink_to_fit();
		cout << "capacity(): " << s.capacity() << "\n\n"; // 0
	}
	{
		String s = "123456789";
		s.erase(2, 3);
		cout << s << " " << s.size() << " " << s.capacity() << endl; // 126789 6 9
		s.erase(2, 100);
		cout << s << " " << s.size() << " " << s.capacity() << endl; // 12 2 9
		s.erase(s.begin(), s.begin()+1);
		cout << s << " " << s.size() << " " << s.capacity() << endl; // 2 1 9
		s.erase(s.begin());
		cout << s << " " << s.size() << " " << s.capacity() << "\n\n"; // null 0 9
	}
	{
		String s("1234");
		String s1("abcdef");
		s.append(s1, 0, 2);
		cout << s << endl; // 1234ab
		s.insert(1, 1, 'c');
		cout << s << endl; // 1c234ab
		s.insert(1, 10, 'a');
		cout << s << endl; // 1aaaaaaaaaac234ab
		String s2("123");
		s2.insert(0, "abc", 2);
		cout << s2 << endl; // 1ab23
		String s3("123");
		s3.insert(s3.begin(), 4, 'c');
		cout << s3 << "\n\n"; // cccc123
	}
	{
		String s("1234");
		cout << *s.begin() << endl; // 1
		*(s.end()-1) = 'a';
		cout << s << "\n\n"; // 123a
	}
	{
		String s;
		s.assign(std::move(String("123123")));
		cout << s << endl; // 123123
		s.assign(10, 'c');
		cout << s << endl; // cccccccccc
		s.resize(1);
		String s1("1234567890");
		s.assign(s1, 1, 100);
		cout << s << endl; // 234567890
		String s2;
		s2.assign("abcdefg", 3);
		cout << s2 << "\n\n"; // abc
	}
	{
		String s("1234");
		String s1("12345");
		String s2("1145");
		String s3("1234");
		cout << s.compare(s1) << endl; // -1
		cout << s.compare(s2) << endl; // 1
		cout << s.compare(s3) << endl; // 0
		cout << s.compare("1234") << endl; // 0
		cout << s.compare("12345") << endl; // -1
		cout << s.compare("1123") << endl; // 1
		cout << s.compare(0, 3, "1234", 2) << endl; // 1
		const char* s4 = "234";
		cout << s.compare(0, 3, s4) << endl; // -1
		cout << s.compare(0, 3, s1) << endl; // -1
		cout << s.compare(0, 3, s1, 0, 3) << "\n\n"; // 0
	}
	{
		String s = "0123456789abcdefghij";
	    cout << s.substr(10) << endl; // abcdefghij
	    cout << s.substr(5, 3) << endl; // 567
	    cout << s.substr(12, 100) << endl; // cdefghij
	    cout << s.substr(s.size()-3, 50) << "\n\n"; // hij
	}
	{
		String s("123456");
		char str[7];
		int i = s.copy(str, 3, 2);
		str[i] = '\0';
		cout << str << "\n\n"; // 345
	}
	{
		String s1("123");
		String s2("456");
		cout << s1+s2 << endl; // 123456
		//cin >> s1;
		cout << s1 << "\n\n";
	}
	{
		int a = 2147483648;
		String s = to_string(a); // -2147483648
		cout << s << endl;
		double f = 23.43;
	    double f2 = 1e-9;
	    double f3 = 1e40;
	    double f4 = 1e-40;
	    double f5 = 123456789;
	    String f_str = to_string(f);
	    String f_str2 = to_string(f2); // Note: returns "0.000000"
	    String f_str3 = to_string(f3); // Note: Does not return "1e+40".
	    String f_str4 = to_string(f4); // Note: returns "0.000000"
	    String f_str5 = to_string(f5);
	    std::cout << "std::cout: " << f << '\n' // 23.43
	              << "to_string: " << f_str  << "\n\n" // 23.430000
	              << "std::cout: " << f2 << '\n' // 1e-009
	              << "to_string: " << f_str2 << "\n\n" // 0.000000
	              << "std::cout: " << f3 << '\n' // 1e+400
	              << "to_string: " << f_str3 << "\n\n" // 10000000000000000303786028427003666890752.000000
	              << "std::cout: " << f4 << '\n' // 1e-400
	              << "to_string: " << f_str4 << "\n\n" // 0.000000
	              << "std::cout: " << f5 << '\n' // 1.23457e+008
	              << "to_string: " << f_str5 << "\n\n"; // 123456789.000000
	}
	{
		String s1 = "123456";
		String s2 = "34";
		cout << s1.find(s2, 1) << endl; // 2
		cout << s1.find("34", 1) << endl; // 2
		cout << s1.find("34", 0, 1) << endl; //2
		cout << s1.find('3', 1) << endl; // 2

		cout << s1.rfind(s2, 4) << endl; // 2
		cout << s1.rfind("45") << endl; // 3
		cout << s1.rfind("23", 4, 1) << endl; // 1
		cout << s1.rfind('2', 3) << endl; // 1

		cout << s1.find_first_of(s2, 0) << endl; // 2
		cout << s1.find_first_of("56", 0, 3) << endl; // 4
		cout << s1.find_first_of("45", 4) << endl; // 4
		cout << s1.find_first_of('2', 2) << endl; // npos

		cout << s1.find_first_not_of(s2, 2) << endl; // 4
		cout << s1.find_first_not_of("56", 0, 3) << endl; // 0
		cout << s1.find_first_not_of("45", 4) << endl; // 5
		cout << s1.find_first_not_of('1', 2) << endl; // 2

		cout << s1.find_last_of(s2, 5) << endl; // 3
		cout << s1.find_last_of("56", 5, 3) << endl; // 5
		cout << s1.find_last_of("45", 4) << endl; // 4
		cout << s1.find_last_of('2', 2) << endl; // 1

		cout << s1.find_last_not_of(s2, 5) << endl; // 5
		cout << s1.find_last_not_of("56", 5, 3) << endl; // 3
		cout << s1.find_last_not_of("45", 4) << endl; // 2
		cout << s1.find_last_not_of('2', 2) << endl; // 2
	}
}
