#ifndef TESTER_HPP
#define TESTER_HPP

#if TEST  // CREATE A REAL STL EXAMPLE
#include <iterator>
#include <map>
#include <set>
#include <stack>
// #include <type_traits> c++11
#include <vector>
namespace ft = std;
#else
#include "../containers/map.hpp"
#include "../containers/set.hpp"
#include "../containers/stack.hpp"
#include "../containers/vector.hpp"
#include "../utils/algorithm.hpp"
#include "../utils/iterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/util.hpp"
#endif

#include <stdlib.h>
#include <time.h>  // for clock()

#include <algorithm>  // std::copy
#include <cmath>    // hypot set
#include <cstddef>  // size_t
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>  // cout
#include <iterator>  // std::iterator_traits
#include <list>      // std::list
#include <numeric>
#include <string>
#include <typeinfo>  // typeid

#define cout std::cout
#define endl std::endl
#define cerr std::cerr
#define rep(i, n) for (int i = 0; i < n; ++i)

//// tester

void vector_test();
void stack_test();
void map_test();
void set_test();
void util_test();
void review_test();

//// helper
double dist(double x1, double y1);
void bitout(size_t n);
#endif