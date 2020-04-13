## Memory Management: Memory-Mapped Files

This module covers the usage and semantics of memory-mapped files on Windows.

### Key Concepts

- File mappings backed by the filesystem
- File mappings backed by a system pagefile
- Win32 memory mapped file API
- Standard Win32 file IO versus memory-mapped file IO tradeoffs

### Reading Materials

- _Windows System Programming, Fourth Edition_: Pages 149-160
    - This section introduces the usage of memory-mapped files.
- _Windows Via C/C++, Fifth Edition_: Pages 463-518
    - This section provides a description of memory-mapped file usage that is far more in-depth than the previously cited resource. 

### Checks on Learning

- There are three (3) high-level steps involved in prepared a memory-mapped file for read or write operations. What are these steps?
- Once one has obtained a view of a mapped file, how does one perform read and write operations on the underlying file?
- What are the implications of providing the value `INVALID_HANDLE_VALUE` as the first argument to `CreateFileMapping()`? 
- Is is possible for multiple processes to share access to a file mapping object? 
- Provide one instance in which it would be preferable to use the standard Win32 file IO pattern (`CreateFile()`, `ReadFile()`/`WriteFile()`, `CloseHandle()`) over memory-mapped file IO.
- Provide on instance in which it would be preferable to use memory-mapped file IO over the standard Win32 file IO pattern.