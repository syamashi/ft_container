#include <iostream>
#include <string>
#include <deque>
#include <list>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
//	#include <map.hpp>
//	#include <stack.hpp>
	#include "vector.hpp"
#endif

#include <stdlib.h>

template < typename T >
void destroy_at( T * location ){
	location->~T();
}
int main(){
	ft::vector<int> A(2);
	std::vector<int> B(10);
	A[0] = 1;
	std::cout << A[2] << std::endl;
	std::cout << A.end() << std::endl;
}