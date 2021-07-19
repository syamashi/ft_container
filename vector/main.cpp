#include "Vector.hpp"
#include <iostream>
#include <vector>

int main() {
	std::vector<int> A(100);
	A[0]=1;

	ft::vector<size_t> B(100);
	std::cout << A[0] << std::endl;
}
