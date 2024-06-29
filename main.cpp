#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "header.h"
#include "injector/getpid.h"
#include "utility/logger.h"

int main()
{
	const char *processName = "PlantsVsZombies.exe";
	DWORD processId = GetProcessId(processName);
	processId = static_cast<int>(processId);
	LOG_INFO("Process ID: " + processId)
	std::cin.get();
	return 0;
}