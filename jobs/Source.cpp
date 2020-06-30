#include <Windows.h>
#include <string>

#include <iostream>

void logError(const WCHAR* wstr);
void logDebug(const WCHAR* wstr);
void logInfo(const WCHAR* wstr);


int wmain(int argc, WCHAR** argv)
{
	//create jobobj
	HANDLE jobHandle = CreateJobObject(NULL, NULL);
	if (NULL == jobHandle)
	{
		logError(L"CreateJobObject");
	}

	JOBOBJECT_BASIC_UI_RESTRICTIONS jobUIRestrict = { 0 };
	jobUIRestrict.UIRestrictionsClass = JOB_OBJECT_UILIMIT_READCLIPBOARD;

	if (!SetInformationJobObject(jobHandle, JobObjectBasicUIRestrictions, &jobUIRestrict, sizeof(JOBOBJECT_BASIC_UI_RESTRICTIONS)))
	{
		logError(L"SetInformationJobObject");
		CloseHandle(jobHandle);
	}
	

	if (2 > argc)
	{
		logInfo(L"No PIDs given");
	}

	//for pid in pids
	for (int i = 1; i < argc; i++)
	{
		//parse args
		DWORD procID = 0;
		try
		{
			procID = wcstoul(argv[i], NULL, 0);
		}
		catch (std::exception)
		{
			continue;
		}

		//get remote proc handle
		HANDLE procHandle = OpenProcess(PROCESS_SET_QUOTA | PROCESS_TERMINATE, NULL, procID);
		if (NULL == procHandle)
		{
			logError(L"OpenProcess");
		}
		//add proc to job obj
		else if (!AssignProcessToJobObject(jobHandle, procHandle))
		{
			logError(L"AssignProcessToJobObject");
		}
		CloseHandle(procHandle);
	}
	//cleanup
	CloseHandle(jobHandle);
	return 0;
}

void logError(const WCHAR *wstr)
{
	wprintf(L"[-] %s\n", wstr);
}

void logDebug(const WCHAR *wstr)
{
	wprintf(L"[!] %s\n", wstr);
}

void logInfo(const WCHAR* wstr)
{
	wprintf(L"[ ] %s\n", wstr);
}