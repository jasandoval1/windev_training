## Essential Input Output Operations in User Mode

This module will cover the basics of performing IO operations in user-mode Windows applications.

### Key Concepts

- Win32 API functions for creating, opening, reading, writing, and closing files
- Console IO and the Windows standard devices
- Functions provided by the Win32 API for working with the filesystem.

### Reading Material

- _Windows System Programming, Fourth Edition_ Pages 25-34, 38-58
    - This section describes the basics of performing simple user-mode file and console IO using the Win32 API. It also covers the basics of file and directory management.
- _Windows System Programming, Fourth Edition_ Pages 59-86
    - This section picks up where the previous section left off and describes more advanced strategies for working with the filesystem via the Win32 API.
- _Windows Via C/C++, Fifth Edition_ Pages 289-305
    - While it encompasses some overlap with the two previous sections, this section provides additional background on the details of synchronous IO operations.

### Exercises

- [Reading Files](./reading-files)

### Checks on Learning

- How are files represented and managed within the context of a Windows process? How does a program request and obtain access to a specified file?
- How does the `ReadFile()` function handle consecutive reads to the same file from the same process context?
- What guarantees does the successful return of the `WriteFile()` function make with regards to the persistence of the requested data to the underlying file on disk? 
- How are the standard input, output, and error devices accessed from the context of a Windows program? 
- How does a standard user program detach itself from its active console? How does it create a new console?
- In simple Windows programs built from the commandline or from within Visual Studio, we typically do not need to call `AllocConsole()` to attach our process to a console, why is this the case?
- How might one read to or write from a specific offset within a specified file?
- Describe one instance in which you might prefer to utilize the file manipulation functions provided by the C Runtime Library over those provided by the Win32 API.
- Describe one instance in which you might prefer to utilize the file manipulation functions provided by the Win32 API over those provided by the C Runtime Library.