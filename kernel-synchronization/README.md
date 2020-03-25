## Synchronization with Kernel Objects

This module picks up where the previous module left off by exploring the various synchronization primitives exposed by the Windows kernel in the form of _dispatcher objects_. Because these primitives are kernel objects, they may be safely shared among multiple processes running on the same system, and thus may be used to synchronize operations among threads running in different process contexts.

### Reading Material

- _Windows 10 System Programming_: "Thread Synchronization (Inter-Process)"
    - This section skips much of the conceptual background provided by the previously cited references in favor practical examples of use of the various kernel synchronization primitives.