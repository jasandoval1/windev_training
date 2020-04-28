// handle_table.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 handle_table.cpp

#include <windows.h>

#include <string>
#include <iostream>
#include <string_view>

constexpr auto const STATUS_SUCCESS_I = 0x0;
constexpr auto const STATUS_FAILURE_I = 0x1;

constexpr auto const NAME_MAX_LEN = 128;

void error(
    std::string_view    msg,
    unsigned long const code = ::GetLastError()
    )
{
    std::cout << "[-] " << msg
        << " Code: " << code
        << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "[-] Invalid arguments\n"
            << "Usage: " << argv[0] << " <EVENT NAME>\n";
        return STATUS_FAILURE_I;
    }

    wchar_t event_name[NAME_MAX_LEN];
    auto converted = size_t{};
    ::mbstowcs_s(&converted, event_name, argv[1], NAME_MAX_LEN-1);
    if (converted == 0 || converted == NAME_MAX_LEN)
    {
        std::cout << "Invalid name provided\n";
        return STATUS_FAILURE_I;
    }

    auto event = ::CreateEventW(nullptr, TRUE, FALSE, event_name);
    if (NULL == event)
    {
        error("CreateEvent() failed");
        return STATUS_FAILURE_I;
    }

    std::wcout << "[+] Successfully created event: "
        << std::wstring_view{event_name, converted-1} << '\n'
        << "[+] Handle value: " << reinterpret_cast<ULONG_PTR>(event) << '\n';

    std::cin.get();

    ::CloseHandle(event);

    return STATUS_SUCCESS_I;
}