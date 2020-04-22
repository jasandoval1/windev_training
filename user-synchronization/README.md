## Synchronization in User Mode

This module enumerates the various methods available to synchronize operations among threads using only user-mode structures. Because these synchronization primitives do not involve a kernel object, they cannot be shared between processes running on the same system, and thus may only be used to synchronize the operations of threads running within the same process.

### Key Concepts

- The distinction between synchronization mechanisms that may be used to synchronize operations among threads within a single process context and those that may be used to synchronize operations among threads in distinct process contexts
- Interlocked operations and corresponding functions / intrinsics
- Windows Critcal Section (`CRITICAL_SECTION`) structure and usage
- Windows Condition Variable (`CONDITION_VARIABLE`) structure and usage
- Windows Slim Reader/Writer Lock (`SRWLOCK`) structure and usage
- Windows Synchronization Barrier (`SYNCHRONIZATION_BARRIER`) structure and usage
- Windows Waitable Address routines

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 259-279, 309-312, 362-366
    - These sections cover usage of three user-mode synchronization primitives: critical sections, slim reader-writer locks, and condition variables, respectively.
- _Windows Via C/C++, Fifth Edition_: Pages 207-238
    - This section provides a integrated introduction to user-mode inter-process thread synchronization primitives. Note that their is significant overlap with the previously listed resource; choose one to read as the primary and subsequently skim the other to address any content discrepancies.
- _Windows 10 System Programming_: "Thread Synchronization (Intra-Process)"
    - This section provides an overview of the now-familiar user-mode synchronization primitives and also introduces two new(er) synchronization primitives not explored by the previous references: barriers and waitable addresses.

### Exercises

- [Threadsafe Intra-Process Queue](./intraprocess-queue)

### Checks on Learning

- It is possible to write both `InterlockedIncrement()` and `_InterlockedIncrement()` in your program source code to atomically increment a 32-bit integral value. What is the distinction between these two invocations?
- Is it possible to recursively acquire a Windows `CRITICAL_SECTION`? What are the consequences of this?
- What does the spin count for a Windows `CRITICAL_SECTION` specify? What is the default spin count if a user-specified value is not provided?
- What is the difference between acquiring a Windows Slim Reader/Writer Lock (`SRWLOCK`) in the shared mode versus in the exclusive mode?
- With which synchronization primitives may a Windows `CONDITION VARIABLE` be associated? Must it be associated with a synchronization primitive in order to function?
- What is the difference between the Win32 functions `WakeConditionVariable()` and `WakeAllConditionVariable()`?
- Under what conditions are threads waiting on a Windows `SYNCHRONIZATION_BARRIER` released?