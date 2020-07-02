#include <Windows.h>
#include <string>

#define MAX_THREADS 20

void logInfo(const WCHAR* wstr);
void logError(const WCHAR* wstr);
void logDebug(const WCHAR* wstr);

DWORD isPrime(LPVOID lpParam);

int wmain(int argc, WCHAR** argv)
{
	//check arg count
	if (3 != argc)
	{
		logInfo(L"Usage: ./primecounter <start> <end>");
	}

	//parse args
	unsigned long long start = 0;
	unsigned long long end = 0;
	try
	{
		start = wcstoull(argv[1], NULL, 0);
		end = wcstoull(argv[2], NULL, 0);
	}
	catch (std::exception)
	{
		exit(EXIT_FAILURE);
	}
	if (start > end)
	{
		logInfo(L"start value must be less than end value");
	}
	HANDLE threadHandles[MAX_THREADS];
	unsigned long long threadData[MAX_THREADS];

	unsigned long long threadNum = end - start;
	unsigned long long counter = 0;
	//iterate values
	while (threadNum)
	{
		int i = 0;
		for (; i <= threadNum && i < MAX_THREADS; i++)
		{
			//create thread
			threadData[i] = i + start;
			threadHandles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)isPrime, &threadData[i], 0, NULL);
			if (NULL == threadHandles[i])
			{
				logError(L"CreateThread");
				exit(EXIT_FAILURE);
			}
		}

		if (WAIT_OBJECT_0 != WaitForMultipleObjects(i, threadHandles, TRUE, INFINITE))
		{
			logError(L"WaitForMultipleObjects");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i <= threadNum && i < MAX_THREADS; i++)
		{
			DWORD retVal = 0;
			if (!GetExitCodeThread(threadHandles[i], &retVal))
			{
				logError(L"GetExitCodeThread");
				exit(EXIT_FAILURE);
			}
			if (retVal)
			{
				counter++;
			}
			CloseHandle(threadHandles[i]);
		}
		if (i > threadNum)
		{
			break;
		}
		start += i ;
		threadNum = end - start;
	}
	wprintf(L"there were %llu primes", counter);
	exit(EXIT_SUCCESS);
}

void logInfo(const WCHAR* wstr)
{
	wprintf(L"[ ] %s", wstr);
}

void logError(const WCHAR* wstr)
{
	wprintf(L"[-] %s", wstr);
}

void logDebug(const WCHAR* wstr)
{
	wprintf(L"[!] %s", wstr);
}

DWORD isPrime(LPVOID lpParam)
{
	unsigned long long num = *(unsigned long long*)lpParam;
	if (num < 3)
	{
		return 0;
	}

	unsigned long long limit = (unsigned long long)sqrt((double)num);
	for (unsigned long long i = 2; i <= limit; ++i)
	{
		if (num % i == 0)
		{
			return 0;
		}
	}

	return 1;
}