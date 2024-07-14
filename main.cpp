#include <iostream>


int main()
{
	int a = 10;
	int *b = &a;

	std::cout << "Value of a: " << a << std::endl;
	std::cout << "Address of a: " << &a << std::endl;
	std::cout << "Value of b: " << *b << std::endl;
	std::cout << "Address of b: " << &b << std::endl;
}