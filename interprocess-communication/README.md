## Interprocess Communication

This module explores the essentials of the interprocess communication mechanisms provided by the Win32 API. 

### Key Concepts

- Windows IPC mechanisms and their interface exposed by Win32
- Anonymous pipes and their usage
- Named pipes and their usage
- Mailslots and their usage 
- Strengths and limitations of Windows IPC mechanisms
- Patterns for effective use of Windows IPC mechanisms

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 379-410
    - This section introduces the three primary interprocess communication (IPC) mechanisms exposes by the Win32 API: anonymous pipes, named pipes, and mailslots. 
- _Windows Internals, Sixth Edition, Part 1_: Pages 612-617
    - This section provides a brief look behind the scenes of the implementation of mailslots and named pipes.

### Checks on Learning

- Anonymous pipes, as the name suggests, do not support the assignment of a human-readable name in the way that named pipes do. How is this limitation reflected in the way anonymous pipes are managed by the Object Manager?
- Provide two ways in which it is possible to share an anonymous pipe instance between processes in order to accomplish interprocess communication.
- The semantics of Windows named pipes distinguishes between _client_ pipe instances and _server_ pipe instances. What Win32 API function is used to open a new _client_ pipe instance? What Win32 API function is used to open a new _server_ pipe instance?
- What are the implications of the `PIPE_TYPE_BYTE` and `PIPE_TYPE_MESSAGE` flags used when creating a new instance of a named pipe?
- What are the implications of the `PIPE_WAIT` and `PIPE_NOWAIT` flags used when creating a new instance of a named pipe?
- Microsoft recommends that the `PIPE_NOWAIT` flag not be utilized to implement asynchronous IO semantics with a named pipe. What alternatives are available in the event that you want to write a program that performs named pipe reads and writes asynchronously? 
- Windows named pipe are often referred to as a full-duplex communications mechanism. However, the semantics of read and write operations on named pipes differ in a at least one critical way from the semantics of read and write operations on sockets. What is this critical distinction? (_hint_: it involves the conditions under which a write operation completes).
- What is the maximum message size that Windows mailslots support for multicast communications?