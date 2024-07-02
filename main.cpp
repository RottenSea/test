#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#include "header.h"
#include "injector/getpid.h"
#include "logger.h"

// 获取进程ID
DWORD GetProcessID(const wchar_t *processName)
{
	DWORD processID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32W pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32W);
		if (Process32FirstW(hSnap, &pe32))
		{
			do
			{
				if (wcscmp(pe32.szExeFile, processName) == 0)
				{
					processID = pe32.th32ProcessID;
					break;
				}
			} while (Process32NextW(hSnap, &pe32));
		}
		CloseHandle(hSnap);
	}
	return processID;
}

// 获取模块基地址
uintptr_t GetModuleBaseAddress(DWORD processID, const wchar_t *moduleName)
{
	uintptr_t moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32W me32;
		me32.dwSize = sizeof(MODULEENTRY32W);
		if (Module32FirstW(hSnap, &me32))
		{
			do
			{
				if (wcscmp(me32.szModule, moduleName) == 0)
				{
					moduleBaseAddress = (uintptr_t)me32.modBaseAddr;
					break;
				}
			} while (Module32NextW(hSnap, &me32));
		}
		CloseHandle(hSnap);
	}
	return moduleBaseAddress;
}

// 读取多级指针指向的地址
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int offset : offsets)
	{
		ReadProcessMemory(hProc, (BYTE *)addr, &addr, sizeof(addr), 0);
		addr += offset;
	}
	return addr;
}

int main()
{
	Logger::Initialize();

	const wchar_t *processName = L"PlantsVsZombies.exe";
	DWORD processID = GetProcessId(processName);

	if (static_cast<int>(processID) == 0)
	{
		std::cin.get();
		return 1;
	}

	LOG_INFO("Process ID: " + std::to_string(processID))

	uintptr_t moduleBase = GetModuleBaseAddress(processID, processName);
	if (moduleBase == 0)
	{
		std::wcerr << L"无法获取模块基地址: " << processName << std::endl;
		return 1;
	}

	std::cin.get();
	return 0;
}