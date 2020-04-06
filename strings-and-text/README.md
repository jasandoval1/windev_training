## Working with Strings and Text

This module will cover the essentials of working with strings and text on Windows platforms.

### Key Concepts

- Multi-byte character string (MBCS) and Unicode character encodings
- The distinction between ANSI and Unicode function usage in the Win32 API
- MBCS to Unicode string conversion and the various APIs available for performing this conversion
- Unicode to MBCS string conversion and the various APIs available for performing this conversion
- Safe string conversion functions
- Safe string manipulation functions

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 34-37
    - This section introduces the bare necessities of the differing character types used in the Win32 API.
- _Windows via C/C++, Fifth Edition_: Pages 11-32
    - This section goes into further detail regarding the character sets available under the Win32 API and introduces various methods for working with strings and text including the functions provided by both the Win32 API and the C Runtime Library.
- _Windows 10 System Programming_: "Working With Strings"
    - This section provides an updated and abridged look at character and string manipulation under Win32.
- [MSDN: CRT String Manipulation](https://docs.microsoft.com/en-us/cpp/c-runtime-library/string-manipulation-crt?view=vs-2019)
    - This article provides your one-stop-shop for character and string manipulation functions provided by the C Runtime Library.
- [MSDN: Strsafe](https://docs.microsoft.com/en-us/windows/win32/menurc/strsafe-ovw)
    - This article provides an overview of the _strsafe_ API (provided by the `strsafe.h` header) which provides an alternative API for working with strings exported directly by Windows.

### Exercises

- [Examining Strings in Memory](./strings-in-memory)

### Checks on Learning

- What is the native character encoding used by Windows?
- What is the distinction between the `UNICODE` and `_UNICODE` macro definitions?
- What is the purpose of the `TCHAR` data type?
- Within a Windows program, `CreateProcess()`, `CreateProcessA()`, and `CreateProcessW()` all represent valid calls that result in the creation of a new process. What is the distinction between these three invocations?
- Familiar C Standard Library functions like `strcpy()` and and `strnlen()` have corresponding "secure" implementations that are suffixed with `_s` (e.g. `strcpy_s()` and `strnlen_s()`). What additional functionality do these secure implementations provide over the standard implementations?
- The Microsoft Visual C/C++ Runtime Library string manipulation functions `strcpy_s()` and `wcscpy_s()` (among others) accept a `dest_size` argument that specifies the size of the destination buffer. In what units is this size expressed?
- The safe string manipulation functions provided by the Windows `strsafe.h` header often come in two distinct variations e.g. `StringCbCopy()` and `StringCchCopy()`. What is the difference between these implementations?