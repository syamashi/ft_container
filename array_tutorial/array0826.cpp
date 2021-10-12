#if TEST //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map>
	#include <stack>
	#include <vector>
	#include "array0826.hpp"
#endif

#include <stdlib.h>
#include <iostream>

template< typename T >
void titleout(T & s){
	static int no;
	std::cout << std::endl << " --- [" << no << "] " << s << " --- " << std::endl;
	++no;
}

int main(){
	titleout("A ++it");
	ft::array<int, 10> A = {0,1,2,3,4,5,6,7,8,9};

	for (auto it = A.begin(); it != A.end(); ++it){
		std::cout << *it << " ";
	}
	titleout("A --it");
	for (auto it = A.end(); it != A.begin(); --it){
		std::cout << *it << " ";
	}

	titleout("A it++");
	for (auto it = A.begin(); it != A.end(); it++){
		std::cout << *it << " ";
	}
	titleout("A it--");
	for (auto it = A.end(); it != A.begin(); it--){
		std::cout << *it << " ";
	}

	titleout("A it+=2");
	for (auto it = A.begin(); it != A.end(); it+=2){
		std::cout << *it << " ";
	}
	titleout("A it-=2");
	for (auto it = A.end(); it != A.begin(); it-=2){
		std::cout << *it << " ";
	}

	titleout("A[]");
	for (auto it = A.begin(); it != A.end(); ++it){
		std::cout << it[0] << " ";
	}

	auto it = A.begin();
	it = A.begin();

	ft::array<int, 10>::const_iterator cit = it;
	
	titleout("A[100]");
	std::cout << A[100] << std::endl;

	titleout("A.at(100)");
	try{
		std::cout << A.at(100) << std::endl;
	}
	catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
}