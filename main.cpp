#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#include "header.h"
#include "injector/getpid.h"
#include "logger.h"

int main()
{
	Logger::Initialize();

	const char *processName = "PlantsVsZombies.exe";
	DWORD processID = GetProcessId(processName);
	int processid = static_cast<int>(processID);
	if (processid == 0)
	{
		std::cin.get();
		return 1;
	}
	LOG_INFO("Process ID: " + std::to_string(processid))

	std::cin.get();
	return 0;
}