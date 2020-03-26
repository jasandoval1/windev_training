## Advanced IO Operations in User Mode

This module combines concepts and practical knowledge gained in previous modules to introduce several advanced IO mechanisms exposed by the Win32 API and patterns for their effective use.

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 481-518
    - This section provides practical examples of utilizing three of the major asynchronous I/O mechanisms available on Windows: overlapped I/O, extended I/O with callback routines, and I/O completion ports.
- _Windows Via C/C++, Fifth Edition_: Pages 305-338
    - This section provides a brief overview of the asynchronous I/O methods discussed in the previously cited reference, as well as a more in-depth treatment of I/O completion ports.
- _Windows System Programming, Fourth Edition_: Pages 312-324
    - This section provides and overview of several advanced IO topics, including threadpools, I/O completion ports, and the NT6 threadpool API. 
- _Windows Via C/C++, Fifth Edition_: Pages 339-360
    - This section describes basic usage of the Win32 threadpool API.
- _Windows 10 System Programming_: "Thread Pools"
    - This section provides a concise overview of the updated Win32 threadpool API.

### Optional Reading Material

- [Channel9: Thread Pools](https://channel9.msdn.com/Shows/Going+Deep/Inside-Windows-8-Pedro-Teixeira-Thread-pool)
    - A detailed look under the hood of the modern Windows threadpool implementation.
- _Windows Internals, Seventh Edition, Part 1_: Pages 297-300
    - This section gives some information regarding the implementation of the _worker factory_ - the kernel component responsible for spawning new threads utilized by user-mode threadpools.