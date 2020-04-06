// strings.c
//
// Build
//  cl /nologo /W4 strings.c /link /DEBUG

#include <windows.h>
#include <string.h>
#include <stdio.h>

#define MAX_CHARS 256

int main()
{
    __debugbreak();

    PSTR ansi     = (PSTR) HeapAlloc(GetProcessHeap(), 0, MAX_CHARS*sizeof(CHAR));
    PWSTR unicode = (PWSTR) HeapAlloc(GetProcessHeap(), 0, MAX_CHARS*sizeof(WCHAR));

    strcpy_s(ansi, MAX_CHARS, "hello world");
    wcscpy_s(unicode, MAX_CHARS, L"hello world");

    printf("%s\n", ansi);
    printf("%ls\n", unicode);

    HeapFree(GetProcessHeap(), 0, ansi);
    HeapFree(GetProcessHeap(), 0, unicode);
}