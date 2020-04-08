## Windows Threads and the Thread Management API

This module provides both a conceptual introduction to Windows threads as well as a practical overview of the thread management API exposed by Win32.

### Key Concepts

- Distinctions between the Win32 thread API and *nix thread APIs (specifically, pthreads)
- Creating and managing threads
- Thread termination
- Thread scheduling
- Process priority classes and thread priorities
- Basic thread internals

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 223-256
    - This section provides an overview of both the conceptual background regarding Windows threads as well as the basics of the thread management API.
- _Windows Via C/C++, Fifth Edition_: Pages 145-172
    - This section provides an alternative look at the basics of thread management on Windows. Note that their is significant overlap with the previously listed resource; choose one to read as the primary and subsequently skim the other to address any content discrepancies.
- _Windows 10 System Programming_: "Thread Basics"
    - This section provides an introduction to the thread management API and demonstrates various best practices when writing multithreaded applications on Windows.
- _Windows 10 System Programming_: "Thread Scheduling"
    - This section explores some of the "behind the scenes" aspects of Windows threads including thread priorities, scheduling algorithms, and priority boosts. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 193-214
    - This section provides the conceptual background for Windows threads and thread management.

### Optional Reading Material

- _Windows Internals, Seventh Edition, Part 1_: Pages 214-297
    - This section covers the gory details of thread scheduling, context switching, priority boosts, etc.

### Exercises

- [Multithreading without Synchronization: Counting Primes](./counting-primes)

### Checks on Learning

- What is the return value of Win32's `CreateThread()` function? How does this compare to the return value of `pthread_create()`?
- Assuming one possess a handle to the thread in question, what is one mechanism one may use to wait for thread termination?
- What is the difference, if any, between returning from a thread's entry procedure and manually invoking `ExitThread()`?
- What is the primary consideration utilized by the Windows Dispatcher when making scheduling determinations?
- How is a thread's priority determined?
- What is the primary user-mode thread management structure?
- What is the primary kernel-mode thread management structure?