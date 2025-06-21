#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_USER_NUMBER 100
#define MAX_ADMINISTRATOR_NUMBER 100
#define MAX_ENTERPRISE_NUMBER 100
#define MAX_USER_FLIGHT 10
#define MAX_FLIGHT_NUMBER 100

#define MAX_UUID_LENGTH 21
#define MAX_NAME_LENGTH 21
#define MAX_PASSWORD_LENGTH 21
#define MAX_PHONE_LENGTH 12
#define MAX_CODE_LENGTH 31

int visualWidth(const wchar_t *str);
void wprintAlign(const wchar_t *str, int total_width);

typedef struct
{
	char CODE[MAX_CODE_LENGTH];
	char MODEL[MAX_NAME_LENGTH];
	char COMPANY[MAX_NAME_LENGTH];
	char date[11];
	time_t time;
	time_t duration;
	char GATE[MAX_NAME_LENGTH];
	char STARTING[MAX_NAME_LENGTH];
	char DESTINATION[MAX_NAME_LENGTH];
	int praise;
	int num;
	int curr;
} FLIGHT;
FLIGHT flights = {0};
int main()
{
	setlocale(LC_ALL, "");

	strcpy(flights.CODE, "CZ6546");
	strcpy(flights.MODEL, "A321neo");
	strcpy(flights.COMPANY, "中国南方航空");
	strcpy(flights.date, "2025-06-18");
	flights.duration = 11100;
	strcpy(flights.GATE, "411");
	strcpy(flights.STARTING, "杭州萧山国际机场");
	strcpy(flights.DESTINATION, "长春龙嘉国际机场");
	flights.praise = 1000;
	flights.num = 200;
	flights.curr = 100;

	printf("----------航班列表----------\n");
	wprintAlign(L"航班号", 10);
	wprintAlign(L"机型", 10);
	wprintAlign(L"承办公司", 20);
	wprintAlign(L"日期", 12);
	wprintAlign(L"始发地", 20);
	wprintAlign(L"目的地", 20);
	wprintf(L"\n");

	wchar_t tempStr[64];
	mbstowcs(tempStr, flights.CODE, 64);
	wprintAlign(tempStr, 10);
	mbstowcs(tempStr, flights.MODEL, 64);
	wprintAlign(tempStr, 10);
	mbstowcs(tempStr, flights.COMPANY, 64);
	wprintAlign(tempStr, 20);
	mbstowcs(tempStr, flights.date, 64);
	wprintAlign(tempStr, 12);
	mbstowcs(tempStr, flights.STARTING, sizeof(flights.STARTING));
	tempStr[sizeof(tempStr) / sizeof(wchar_t)] = L'\0';
	wprintAlign(tempStr, 20);
	mbstowcs(tempStr, flights.DESTINATION, sizeof(flights.DESTINATION));
	wprintAlign(tempStr, 20);
	wprintf(L"\n");

	getchar();
	return 0;
}

int visualWidth(const wchar_t *str)
{
	int width = 0;
	while (*str)
	{
		if (*str >= 0x4e00 && *str <= 0x9fff) // 中文基本区
			width += 2;
		else
			width += 1;
		str++;
	}
	return width;
}

void wprintAlign(const wchar_t *str, int total_width)
{
	int width = visualWidth(str);
	wprintf(L"%ls", str);
	for (int i = 0; i < total_width - width; ++i)
		wprintf(L" ");
}