## Introduction to Programming on Windows and the Win32 API

This module provides a brief introduction to the Windows programming environment, often by way of contrast with the *NIX programming environment with which most developers possess a greater degree of experience. 

### Key Concepts

- Major similarities and differences between the Win32 API and the API utilized when developing on *NIX systems (typically C Runtime routines)
- Windows data types and non-intuitive type definitions (e.g. `typdef int BOOL`)
- Microsoft Developer Network (MSDN) online documentation

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 10-11, 13-20
    - This short section makes the critical distinction between the Win32 API and the API exposed by the Microsoft Visual C Runtime Library (CRT) and gives some guidance for when to rely on either API. The latter section provides a short example of the use of both APIs and enumerates the pros / cons of each. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 1-8
    - This section provides a brief overview of some information that is nonetheless incredibly valuable, including the Windows version history and the definition of some critical Windows technologies such as the Win32 API, the .NET Framework (now deprecated in favor of .NET Core), and the Windows Runtime.
- [MSDN: Windows Data Types](https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types)

### Checks on Learning

- What is the Windows type used to reference and manage operating system resources within a process? How is this type similar to UNIX file descriptors? How is it different?
- Provide one example of an instance in which you would utilize the C Runtime Library's implementation of some functionality over the implementation provided by the Win32 API.
- Provide one example of an instance in which you would utilize the Win32 API's implementation of some functionality over the implementation provided by the C Runtime Library.
- What is the SDK-provided header in which you can find the type definitions for standard Windows data types? How do access this file?
    