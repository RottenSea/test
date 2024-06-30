#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

#include "getpid.h"
#include "logger.h"

DWORD GetProcessId(const char *processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32);

	DWORD processId;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		LOG_ERROR("Failed to take snapshot of processes. Error code: " + std::to_string(GetLastError()));
	}

	if (Process32First(snapshot, &processInfo))
	{
		int i = 1;
		BOOL flag = true;
		LOG_INFO("Finding process");

		do
		{
			i++;
			std::cout << std::endl;

			if (std::string(processInfo.szExeFile) == processName)
			{
				flag = false;
				LOG_INFO("Process Found Successfully");

				processId = processInfo.th32ProcessID;
			}
		} while (Process32Next(snapshot, &processInfo) && flag);
	}

	else
	{
		LOG_ERROR("Failed to get first process. Error code: " + std::to_string(GetLastError()));
	}
	
	CloseHandle(snapshot);
	return processId;
}
