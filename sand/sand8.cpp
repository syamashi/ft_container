#include <iostream>

void f(int n)
{
	std::cout << n;
}

const void f(const int n)
{
	std::cout << n;
}

int main()
{
	f(2);
	return 0;
}