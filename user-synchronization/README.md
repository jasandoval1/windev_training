## Synchronization in User Mode

This module enumerates the various methods available to synchronize operations among threads using only user-mode structures. Because these synchronization primitives do not involve a kernel object, they cannot be shared between processes running on the same system, and thus may only be used to synchronize the operations of threads running within the same process.

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 259-279, 309-312, 362-366
    - These sections cover usage of three user-mode synchronization primitives: critical sections, slim reader-writer locks, and condition variables, respectively.
- _Windows 10 System Programming_: "Thread Synchronization (Intra-Process)"
    - This section provides an overview of the now-familiar user-mode synchronization primitives and also introduces two new(er) synchronization primitives not explored by the previous references: barriers and waitable addresses.