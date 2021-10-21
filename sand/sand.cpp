#include <map>
#include <stack>
#include <list>         // std::list
#include <vector>
#include <iterator>

#define rep(i, n) for (int i = 0; i < n; ++i)
#include <stdlib.h>
// iterator_traits example
#include <iostream>  // cout
#include <iterator>  // std::iterator_traits
#include <typeinfo>  // typeid
#include <algorithm>    // std::copy
#include <cstddef> // size_t
#include <type_traits>

#define cout std::cout
#define endl std::endl

int main(){

	std::vector<int> V={1,2,3,4,5};

	std::reverse_iterator<std::vector<int>::reverse_iterator> it;
	cout << *it << endl;

	std::reverse_iterator<std::vector<int>::const_iterator> it1 = it.rbegin();
}