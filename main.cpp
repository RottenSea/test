#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	int n = 3;
	for (int i = 0; i < (1 << n); ++i)
	{
		for (int j = 0; j < n; ++j)
		{
		}
	}
	return 0;
}