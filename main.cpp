#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	printf("----------航班列表----------\n");
	wprintf(L"%-10ls%-10ls%-20ls%-8ls%-8ls%-8ls%-20ls%-20ls%-8ls%-8ls%-8ls\n", L"航班号", L"机型", L"承办公司", L"日期", L"出发时间", L"到达时间", L"始发地", L"目的地", L"价格", L"剩余", L"状态");
	getchar();
	return 0;
}