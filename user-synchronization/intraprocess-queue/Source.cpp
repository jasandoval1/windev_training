#include <Windows.h>
#include <string>
#include <queueLib.h>

void logInfo(const WCHAR* wstr);
void logError(const WCHAR* wstr);
void logIDebug(const WCHAR* wstr);

int wmain(int argc, WCHAR** argv)
{
	logInfo(L"Cannot comply. Building in progress");
	unsigned int x = 0;
	
	logInfo(L"Exitting...");
	exit(EXIT_SUCCESS);
}

void logInfo(const WCHAR* wstr)
{
	wprintf(L"[ ] %s\n", wstr);
}

void logError(const WCHAR* wstr)
{
	wprintf(L"[-] %s\n", wstr);
}

void logIDebug(const WCHAR* wstr)
{
	wprintf(L"[!] %s\n", wstr);
}
