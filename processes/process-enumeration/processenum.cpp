#include <Windows.h>
#include <Psapi.h>
#include <string>

#define PROCESSES_SZ 1024

int enumfunction(void);

int wmain(int argc, wchar_t** argv)
{
	enumfunction();
	exit(EXIT_SUCCESS);
}

// enumprocesses usage function
int enumfunction(void)
{
	DWORD processes[PROCESSES_SZ];
	DWORD bytesNeeded;
	if (!EnumProcesses(processes, sizeof(processes), &bytesNeeded))
	{
		exit(EXIT_FAILURE);
	}

	for (DWORD i = 0; i < bytesNeeded / sizeof(DWORD); i++)
	{
		HANDLE procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
		wprintf(L"%ul", processes[i]);
		WCHAR procName[MAX_PATH] = L"<unknown>";
		if (NULL != procHandle)
		{
			HMODULE hMod;
			bytesNeeded = 0;
			if (EnumProcessModules(procHandle, &hMod, sizeof(hMod), &bytesNeeded))
			{
				GetModuleBaseName(procHandle, hMod, procName, MAX_PATH / sizeof(WCHAR));
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
	return 0;
}

// wts usage function
int wtsfunction(void)
{
	return 0;
}