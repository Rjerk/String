# Implementation of std::string class

> reference: [cppreference](http://en.cppreference.com/w/cpp/string/basic_string)

## Completion

### Member functions
- [x] constructor (10/17)
- [x] destructor (1/1)
- [x] operator= (5/6)
- [x] assign (6/10)
- [ ] get_allocator

#### Element access
- [x] at (2/2)
- [x] operator[] (2/2)
- [x] front (2/2)
- [x] back (2/2)
- [x] data (2/2)
- [x] c_str (1/1)
- [ ] operator basic_string_view

#### Iterators
- [x] begin (1/3)
- [ ] cbegin
- [x] end (1/3)
- [ ] cend
- [ ] rbegin/crbegin
- [ ] rend/crend

#### Capacity
- [x] empty (1/1)
- [x] size/length (2/2)
- [x] max_size (1/1)
- [x] reserve (1/1)
- [x] capacity (1/1)
- [x] shrink_to_fit (1/1)
- [x] clear (1/1)
- [x] insert (6/11)
- [x] erase (3/5)
- [x] push_back (1/1)
- [x] pop_back (1/1)
- [x] append (5/9)
- [x] operator+= (4/5)
- [x] compare (6/9)
- [x] replace (5/14)
- [x] substr (1/1)
- [x] copy (1/1)
- [x] resize (2/2)
- [x] swap (1/1)

#### Search
- [x] find (4/5)
- [x] rfind (4/5)
- [x] find_first_of (4/5)
- [x] find_first_not_of (4/5)
- [x] find_last_of (4/5)
- [x] find_last_not_of (4/5)

#### Constant
- [x] npos (1/1)

### Non-member functions
- [x] operator+ (12/12)
- [x] operator== (3/3)
- [x] operator!= (3/3)
- [x] operator<  (3/3)
- [x] operator>  (3/3)
- [x] operator<= (3/3)
- [x] operator>= (3/3)
- [x] std::swap  (1/1)

#### Input/Output
- [x] operator<< (1/1)
- [x] operator>> (1/1)
- [ ] getline

#### Numeric conversions
- [ ] stoi/stol/stoll
- [ ] stoul/stoull
- [ ] stof/stod/stold
- [x] to_string (9/9)

### Literals
- [ ] operator""s

### Helper classes
- [ ] std::hash< std::string>