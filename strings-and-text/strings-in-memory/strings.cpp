// strings.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 strings.cpp /link /DEBUG

#include <windows.h>

#include <string>
#include <cstddef>

constexpr auto MAX_CHARS = 256;

class string
{
    char* m_buffer;

public:
    string(std::size_t n_chars, const char* init) 
        : m_buffer{ new char[n_chars] }
    {
        SecureZeroMemory(m_buffer, n_chars * sizeof(char));
        strcpy_s(m_buffer, n_chars * sizeof(char), init);
    }

    ~string()
    {
        delete[] m_buffer;
    }
};

class wstring
{
    wchar_t* m_buffer;

public:
    wstring(std::size_t n_chars, const wchar_t* init) 
        : m_buffer{ new wchar_t[n_chars] }
    {
        SecureZeroMemory(m_buffer, n_chars * sizeof(wchar_t));
        wcscpy_s(m_buffer, n_chars*sizeof(wchar_t), init);
    }

    ~wstring()
    {
        delete[] m_buffer;
    }
};

int main()
{
    __debugbreak();

    auto ansi    = string{MAX_CHARS, "hello world"};
    auto unicode = wstring{MAX_CHARS, L"hello world"};
}