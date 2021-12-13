#ifndef TESTER_HPP
#define TESTER_HPP

#if TEST  // CREATE A REAL STL EXAMPLE
#include <vector>
#include <stack>
#include <map>
#include <iterator>
#include <type_traits>
namespace ft = std;
#else
#include "../containers/vector.hpp"
#include "../containers/stack.hpp"
#include "../containers/map.hpp"
#include "../utils/iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#endif

#define rep(i, n) for (int i = 0; i < n; ++i)

#include <list>         // std::list
#include <deque>
#include <stdlib.h>
#include <iostream>  // cout
#include <iterator>  // std::iterator_traits
#include <typeinfo>  // typeid
#include <cstddef> // size_t
#include <numeric>
#include <algorithm> // std::copy

#define cout std::cout
#define endl std::endl
#define cerr std::cerr

/*
** tester
*/

void vector_test();
void stack_test();
void map_test();
void set_test();

#endif