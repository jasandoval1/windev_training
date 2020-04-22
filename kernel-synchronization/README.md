## Synchronization with Kernel Objects

This module picks up where the previous module left off by exploring the various synchronization primitives exposed by the Windows kernel in the form of _dispatcher objects_. Because these primitives are kernel objects, they may be safely shared among multiple processes running on the same system, and thus may be used to synchronize operations among threads running in different process contexts.

### Key Concepts

- The distinction between synchronization mechanisms that may be used to synchronize operations among threads within a single process context and those that may be used to synchronize operations among threads in distinct process contexts
- Windows dispatcher objects
- Windows event kernel objects and usage
- Windows mutex kernel objects and usage 
- Windows sempahore kernel object and usage
- Asynchronous Procedure Calls (APCs)

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 279-289
    - This section covers the three most popular kernel synchronization objects: mutexes, semaphores, and events.
- _Windows Via C/C++, Fifth Edition_: Pages 241-288
    - This section provides an alternative description of kernel synchronization objects exposed by the Win32 API, as well as some more advanced usage patterns. Note that their is significant overlap with the previously listed resource; choose one to read as the primary and subsequently skim the other to address any content discrepancies.
- _Windows System Programming, Fourth Edition_: Pages 366-371
    - This section covers the basics of user-mode asynchronous procedure calls (APCs).
- _Windows 10 System Programming_: "Thread Synchronization (Inter-Process)"
    - This section skips much of the conceptual background provided by the previously cited references in favor practical examples of use of the various kernel synchronization primitives.
- _Windows Internals, Sixth Edition, Part 1_: Pages 183-205
    - This section describes the underlying system mechanisms that implement kernel synchronization objects (dispatcher objects).  

### Exercises

- [Threadsafe Inter-Process Queue](./interprocess-queue)

### Checks on Learning

- What are the two states in which Windows dispatcher objects may be?
- What is the difference between a proper Windows dispatcher object and an aggregate dispatcher object?
- What is the common Object Manager structure that all proper Windows dispatcher objects have in common?
- Under what conditions are the following Windows dispatcher objects in the _signalled_ state:
    - Process
    - Thread
    - File
    - Mutex
    - Semaphore
- What are the two types of Windows event objects? What are the characteristics of each of these types?
- Under what conditions does a Windows mutex become abandoned?
- Is it possible to recursively acquire a Windows mutex?
- What happens when a thread calls `WaitForSingleObject()` on a Windows semaphore and the semaphore is in the signalled state? What happens when the semaphore is in the non-signalled state?
- Name three (3) functions provided by the Win32 API that allow the calling thread to enter an alertable wait state.