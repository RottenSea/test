#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int a = 1;
int b = 2;

int main()
{
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;

	int a = 3;
	int b = 4;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;

	{
		int a = 5;
		int b = 6;
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
	}
}