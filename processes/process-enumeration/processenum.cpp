#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <WtsApi32.h>
#include <string>
#include <iostream>

#pragma comment(lib, "WtsApi32.lib")
#define PROCESSES_SZ 1024

int enumfunction(void);
int toolfunction(void);
int wtsfunction(void);

int wmain(int argc, wchar_t** argv)
{
	if (2 != argc)
	{
		exit(EXIT_FAILURE);
	}
	int method = 0;
	try
	{
		method = std::stoi(argv[1]);
	}
	catch (std::out_of_range)
	{
		exit(EXIT_FAILURE);
	}
	catch (std::invalid_argument)
	{
		exit(EXIT_FAILURE);
	}

	int retVal = 1;
	switch (method)
	{
	case(0):
		retVal = enumfunction();
		break;
	case(1):
		retVal = toolfunction();
		break;
	case(2):
		retVal = wtsfunction();
		break;
	default:
		retVal = 1;
	}

	if (0 == retVal)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

// enumprocesses usage function
int enumfunction(void)
{
	DWORD processes[PROCESSES_SZ];
	DWORD procBytes;
	if (!EnumProcesses(processes, sizeof(processes), &procBytes))
	{
		return 1;
	}

	for (DWORD i = 0; i < procBytes / sizeof(DWORD); i++)
	{
		HANDLE procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
		wprintf(L"%ul", processes[i]);
		WCHAR procName[MAX_PATH] = L"<unknown>";
		if (NULL != procHandle)
		{
			HMODULE hMod;
			DWORD bytesNeeded = 0;
			if (EnumProcessModules(procHandle, &hMod, sizeof(hMod), &bytesNeeded))
			{
				GetModuleBaseName(procHandle, hMod, procName, MAX_PATH);
			}
			CloseHandle(procHandle);
		}
		wprintf(L"\t%s\n", procName);
	}
	return 0;
}

// tool help usage function
int toolfunction(void)
{ 
	HANDLE procSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == procSnap)
	{
		return 1;
	}
	PROCESSENTRY32W procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32W);

	if (!Process32FirstW(procSnap, &procEntry))
	{
		CloseHandle(procSnap);
		return 1;
	}

	do
	{
		wprintf(L"%ul\t%s\n", procEntry.th32ProcessID, procEntry.szExeFile);
	} while (Process32Next(procSnap, &procEntry));
	return 0;
}

// wts usage function
int wtsfunction(void)
{
	PWTS_PROCESS_INFO procInfo;
	DWORD procCount;
	if (!WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &procInfo, &procCount))
	{
		return 1;
	}
	for (DWORD i = 0; i < procCount; i++)
	{
		wprintf(L"%ul\t%ws\n", procInfo[i].ProcessId, procInfo[i].pProcessName);
	}
	return 0;
}