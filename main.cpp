#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "header.h"
#include "injector/getpid.h"
#include "logger.h"

int main()
{
	Logger::Initialize();

	const char *processName = "PlantsVsZombies.exe";
	DWORD processId = GetProcessId(processName);
	processId = static_cast<int>(processId);
	LOG_INFO("Process ID: " + std::to_string(processId))
	std::cin.get();
	return 0;
}