## The Windows Memory Management Subsystem and the Memory Management API

This (information dense) module covers the Windows memory management subsystem and the API hierarchy exposed by Win32 and the C Runtime Library for memory management. 

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 131-149
    - This section gives an overview of the user-mode memory management architecture and the Windows heap API.
- _Windows Via C/C++, Fifth Edition_: Pages 371-394
    - This section provides a more comprehensive of the Windows memory management subsystem architecture and explores various properties of user-mode virtual address spaces. 
- _Windows Via C/C++, Fifth Edition_: Pages 519-536
    - This section provides an in-depth treatment of the Windows heap API and explores the implications of user-defined heaps. 
- _Windows System Programming, Fourth Edition_: Pages 149-160
    - This section introduces the usage of memory-mapped files.
- _Windows Via C/C++, Fifth Edition_: Pages 463-518
    - This section provides a description of memory-mapped file usage that is far more in-depth than the previously cited resource. 
- Windows Internals, Seventh Edition, Part 1_: Pages 301-323
    - This section provides a conceptual overview of the memory subsystem and the services it provides to both user-mode and kernel-mode components.
- _Windows Internals, Seventh Edition, Part 1_: Pages 332-347
    - This section provides the conceptual background behind the Windows heap API and the existence of multiple, distinct heap implementations available to user-mode applications. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 348-383
    - This section covers the structure of the virtual address space of Windows applications and the process utilized by the kernel to translate virtual addresses to physical addresses.

### Optional Reading Material

### Exercises

- [C/C++ Runtime Memory Allocations and the Heap API](./runtime-heaps)
