// last_error.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 last_error.cpp

#include <windows.h>

#include <string>
#include <iostream>

int main()
{
    auto buffer = std::string{};
    auto code = unsigned long{};

    for (;;)
    {
        std::cout << "[+] Enter error code (q to quit): ";

        std::getline(std::cin, buffer);

        if ("q" == buffer)
        {
            break;
        }

        try
        {
            code = std::stoul(buffer);
        }
        catch (std::exception const&)
        {
            // std::invalid_argument or std::out_of_range
            std::cout << "[-] Invalid value provided\n";
            continue;
        }

        std::cout << "[+] Setting last error to: "; 
        std::cout << code << '\n';

        ::SetLastError(code);

        std::cout << "[+] GetLastError() returns: "; 
        std::cout << ::GetLastError() << '\n';

        __debugbreak();
    }

    std::cout << "[+] Exiting\n";
}