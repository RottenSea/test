#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "header.h"
#include "injector/getpid.h"

int main()
{

	const char *processName = "PlantsVsZombies.exe";

	DWORD processId = GetProcessId(processName);

	processId = static_cast<int>(processId);

	std::cout << "Process ID: " << processId << std::endl;

	std::cin.get();

	return 0;
}