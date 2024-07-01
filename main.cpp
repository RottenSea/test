#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#include "header.h"
#include "injector/getpid.h"
#include "logger.h"

bool ModifyProcessMemory(DWORD processID, LPVOID baseAddress, const std::vector<SIZE_T> &offsets, LPVOID newValue, SIZE_T size)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (hProcess == NULL)
	{
		std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
		return false;
	}

	LPVOID address = baseAddress;
	for (SIZE_T offset : offsets)
	{
		if (!ReadProcessMemory(hProcess, address, &address, sizeof(address), NULL))
		{
			std::cerr << "Failed to read process memory. Error: " << GetLastError() << std::endl;
			CloseHandle(hProcess);
			return false;
		}
		address = reinterpret_cast<LPVOID>((reinterpret_cast<SIZE_T>(address) + offset));
	}

	SIZE_T bytesWritten;
	BOOL result = WriteProcessMemory(hProcess, address, newValue, size, &bytesWritten);
	if (!result)
	{
		std::cerr << "Failed to write process memory. Error: " << GetLastError() << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	CloseHandle(hProcess);
	return true;
}

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

	LPVOID baseAddress = reinterpret_cast<LPVOID>(0x2A9EC0);
	std::vector<SIZE_T> offsets = {768, 5560};
	int newValue = 5000;
	std::cout << "Modifying memory at " << std::hex << baseAddress << std::endl;
	std::cout << "Offsets: " << std::hex << offsets[0] << " " << std::hex << offsets[1] << std::endl;
	std::cout << "New value: " << newValue << std::endl;

	if (ModifyProcessMemory(processID, baseAddress, offsets, &newValue, sizeof(newValue)))
	{
		std::cout << "Memory modified successfully." << std::endl;
	}
	else
	{
		std::cout << "Failed to modify memory." << std::endl;
	}

	std::cin.get();
	return 0;
}