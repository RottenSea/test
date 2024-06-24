#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

#include "getpid.h"

DWORD GetProcessId(const char *processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32);

	DWORD processId;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to take snapshot of processes. Error code: " << GetLastError() << std::endl;
	}

	if (Process32First(snapshot, &processInfo))
	{
		int i = 1;
		BOOL flag = true;
		std::cout << "Finding Process..." << std::endl;

		do
		{
			i++;
			std::cout << std::endl;

			if (std::string(processInfo.szExeFile) == processName)
			{
				flag = false;
				std::cout << "Process Found Successfully" << std::endl;

				processId = processInfo.th32ProcessID;
			}
		} while (Process32Next(snapshot, &processInfo) && flag);
	}

	else
	{
		std::cerr << "Failed to get first process. Error code: " << GetLastError() << std::endl;
	}

	CloseHandle(snapshot);
	return processId;
}
