## Network Programming on Windows

This module covers the essentials of Windows networking infrastructure and the networking API available on Windows. Ostensibly, this is a relatively large topic composed of many possible sub-topics; for the purposes of this curriculum, the focus will be on the basic networking API exposed via the Windows Sockets API (_WinSock2_).

Note that this module assumes an existing familiarity with network programming under the BSD socket API. Thus, you should be comfortable with using the following functions to write networked applications:

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `connect()`
- `send()`
- `recv()`

### Key Concepts

- The Windows socket API (Winsock2)
- Writing networked applications with the Windows socket API
- Distinctions between the Windows sockets API and the Berkeley sockets API
- Asynchronous IO operations on Windows sockets

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 411-452
    - This section introduces most of the essentials of the Windows sockets API and, importantly, compares and contrasts the networking API exposed by Win32 with the BSD socket API with which may developers are likely more familiar.
- _Windows Internals, Sixth Edition, Part 1_: Pages 591-597
    - This section provides a high-level overview of the architecture of Windows' networking components.
- _Windows Internals, Sixth Edition, Part 1_: Pages 597-603
    - This section provides a conceptual overview of the Winsock API exposed to user-mode applications.

### Checks on Learning

- Where is the Winsock2 API implemented? How do you gain access to this API in your own programs?
- What is the first networking-related action that your program must make when utilizing the Winsock2 API? What status do Winsock2 API functions return if this action is not performed before they are invoked?
- How should your application "clean up" once it has finished using Winsock2 functionality?
- How do you close a socket connection using the Winsock2 API?
- Most UNIX implementations represent sockets as regular file descriptors, implying that standard UNIX IO methods may be used to perform IO on socket (e.g. `read()`, `write()`, etc.). The Winsock2 socket creation functions `socket()` and `WSASocket()` return a `SOCKET` to represent the underlying socket. Is it possible to use standard Win32 IO functions to interact with Windows sockets via this `SOCKET` type?
- How do you retrieve errors associated with failed Winsock2 API calls?
- A common sight in networked Windows applications is the `WIN32_LEAN_AND_MEAN` macro definition. What is the purpose of defining this macro? Why is it necessary?
- Several functions exposed by the Winsock2 API, including `WSASend()` and `WSARecv()`, accept an array of `WSABUF` structures rather than a simple buffer and size in order to specify the data that should be sent or received on the socket. What is the purpose of this additional layer of abstraction?
- One mechanism for performing asynchronous IO with the Winsock2 API is through the use of overlapped operations and `WSAEVENT` handles. Such `WSAEVENT` handles are returned by a call to `WSACreateEvent()`. What is the difference, if any, between the event object returned by a call to `WSACreateEvent()` and that returned by a call to the standard Win32 `CreateEvent()`?
- Suppose you implement an asynchronous network read operation with `WSARecv()` by providing a pointer to a properly-initialized `WSAOVERLAPPED` structure to the call and specifying `NULL` for the `lpCompletionRoutine` parameter. How would you receive notification that the read operation completed? Once the operation completes, how would you query the results of the operation?
- Suppose you implement an asynchronous network read operation with `WSARecv()` by proving a pointer to a valid completion routine (i.e. matching the signature of `LPWSAOVERLAPPED_COMPLETION_ROUTINE`) to the call and specifying a pointer to a properly-initialized `WSAOVERLAPPED` structure for the `lpOverlapped` parameter. How would you receive notification that the read operation completed? Once the operation completed, how would you query the results of the operation?
- What status value do IO-bound Winsock2 functions return when invoked asynchronously (assuming the underlying IO operation does not complete immediately)?
