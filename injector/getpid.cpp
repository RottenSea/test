#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

#include "getpid.h"

DWORD GetProcessId(const char* processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(PROCESSENTRY32);

	DWORD processId ;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to take snapshot of processes. Error code: " << GetLastError() << std::endl;
	}
	
	if (Process32First(snapshot, &processInfo))

	{
		int i = 1;
		std::cout << "i = " << i << std::endl;
		std::cout << "----------------------------------" << std::endl;
		std::cout << "Process Name: " << processInfo.szExeFile << std::endl;
		std::cout << "Process ID: " << processInfo.th32ProcessID << std::endl;
		std::cout << "Parent Process ID: " << processInfo.th32ParentProcessID << std::endl;
		std::cout << "Threads: " << processInfo.cntThreads << std::endl;
		std::cout << "Priority Class: " << processInfo.pcPriClassBase << std::endl;
		std::cout << "----------------------------------" << std::endl;
		std::cout << std::endl;

		do
		{
			i++;
			std::cout << "i = " << i << std::endl;
			std::cout << "----------------------------------" << std::endl;
			std::cout << "Process Name: " << processInfo.szExeFile << std::endl;
			std::cout << "Process ID: " << processInfo.th32ProcessID << std::endl;
			std::cout << "Parent Process ID: " << processInfo.th32ParentProcessID << std::endl;
			std::cout << "Threads: " << processInfo.cntThreads << std::endl;
			std::cout << "Priority Class: " << processInfo.pcPriClassBase << std::endl;
			std::cout << "----------------------------------" << std::endl;
			std::cout << std::endl;
			if ((processInfo.szExeFile) == processName)
			{
				std::cout << "process found" << std::endl;
				processId = processInfo.th32ProcessID;
			}
		} 
		while (Process32Next(snapshot, &processInfo));
	}

	else
	{
		std::cerr << "Failed to get first process. Error code: " << GetLastError() << std::endl;
	}
	
	CloseHandle(snapshot);
	return processId;
}
