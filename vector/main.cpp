#include "Vector.hpp"
#include <iostream>
#include <vector>

int main() {
	std::vector<int> A(100);
	A[0]=1;
	std::cout << A[0] << std::endl;

	ft::vector<int> B(10, 1);
	std::cout << B[0] << std::endl;
}
