# Implementation of std::string class

> reference: http://en.cppreference.com/w/cpp/string/basic_string

## Completion

### Member functions
- constructor (10/17)
- destructor (1/1)
- operator= (5/6)
- assign (6/10)
- get_allocator (x)

#### Element access
- at (2/2)
- operator[] (2/2)
- front (2/2)
- back (2/2)
- data (2/2)
- c_str (1/1)
- operator basic_string_view (x)

#### Iterators
- begin (1/3)
- cbegin (x)
- end (1/3)
- cend (x)
- rbegin/crbegin (x)
- rend/crend (x)

#### Capacity
- empty (1/1)
- size/length (2/2)
- max_size (1/1)
- reserve (1/1)
- capacity (1/1)
- shrink_to_fit (1/1)
- clear (1/1)
- insert (6/11)
- erase (3/5)
- push_back (1/1)
- pop_back (1/1)
- append (5/9)
- operator+= (4/5)
- compare (6/9)
- replace (5/14)
- substr (1/1)
- copy (1/1)
- resize (2/2)
- swap (1/1)

#### Search
- find (4/5)
- rfind (4/5)
- find_first_of (4/5)
- find_first_not_of (4/5)
- find_last_of (4/5)
- find_last_not_of (4/5)

#### Constant
- npos (1/1)

### Non-member functions
- operator+ (12/12)
- operator== (3/3)
- operator!= (3/3)
- operator<  (3/3)
- operator>  (3/3)
- operator<= (3/3)
- operator>= (3/3)
- std::swap  (1/1)

#### Input/Output
- operator<< (1/1)
- operator>> (1/1)
- getline (x)

#### Numeric conversions
- stoi/stol/stoll (x)
- stoul/stoull (x)
- stof/stod/stold (x)
- to_string (9/9)

### Literals
- operator""s (x)

### Helper classes
- std::hash<std::string> (x)
