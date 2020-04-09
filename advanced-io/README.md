## Advanced IO Operations in User Mode

This module combines concepts and practical knowledge gained in previous modules to introduce several advanced IO mechanisms exposed by the Win32 API and patterns for their effective use.

### Key Concepts

- The Win32 asynchronous IO API
- Overlapped IO
- Extended IO with callback routines
- IO Completion Ports
- Asynchronous IO with the Windows threadpool
- Benefits and drawbacks of using asynchronous IO in your applications

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

### Exercises

- [Reading a File with Overlapped IO](./overlapped-read)
- [Reading a File with Extended IO and Completion Routines](./extended-read)
- [Reading a File with an IO Completion Port](./iocp-read)
- [Reading a File with the Windows Threadpool](./threadpool-read)

### Checks on Learning

- What is the significance of a file's file pointer when the file is created or opened with the `FILE_FLAG_OVERLAPPED` flag?
- On successful initiation of an _overlapped_ IO operation, a call to `ReadFile()` or `WriteFile()` returns `FALSE`. What does `GetLastError()` return in this case?
- What do `ReadFileEx()` and `WriteFileEx()` return on successful initiation of an asynchronous (_extended_) IO operation?
- When an _overlapped_ IO operation is initiated, such as with `ReadFile()` or `WriteFile()`, an `OVERLAPPED` structure is provided as a formal parameter to the call. Who is responsible for the storage and lifetime of the `OVERLAPPED` structure in the event that the operation is initiated successfully?
- One member of the `OVERLAPPED` structure is a handle to a Windows event object. Are there any restrictions on the type of event that may be used for this purpose?
- When an _overlapped_ IO operation is initiated, is it possible to wait on IO completion from a thread in the same process context that is distinct from the one that initiated the operation? From a thread in a different process context?
- Suppose an _extended_ IO operation is initiated with a specified callback function. When the IO operation eventually completes and this callback function is invoked, in what thread context does this occur?
- What Win32 API function(s) are used by threads to wait on IO completion port completion events (IO or otherwise)?
- How does a thread that services IO completion port completion events uniquely identify the IO operation that completed?
- What determines the number of threads associated with an IO completion port that service completion events? What determines the number of threads that service IO completion events when the Windows threadpool is used?