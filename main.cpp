#include <iostream>
#include <Windows.h>
void add(int a, int *b)
{
	a += *b;

	*b = a;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << *b << std::endl;
}
int main()
{
	int a = 10;
	int *b = &a;
	int c = a + *b;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << *b << std::endl;
	std::cout << "c = " << c << std::endl;

	add(a, b);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << *b << std::endl;
	std::cout << "c = " << c << std::endl;

	return 0;
}