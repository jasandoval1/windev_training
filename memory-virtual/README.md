## Memory Management: Windows Memory Architecture and the Virtual API

This module covers the high-level architecture of the Windows memory management subsystem and the API exposed by Win32 for coarse-grained memory operations - the Virtual API.

### Key Concepts

- High-level architecture of the Windows memory management subsystem
- Memory layout of Windows user-mode processes
- Windows memory page protections
- Windows memory page states
- Virtual address translation
- Win32 Virtual API

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 131-134
    - This section gives a brief overview of the user-mode memory management architecture.
- _Windows Via C/C++, Fifth Edition_: Pages 371-394
    - This section provides a more comprehensive of the Windows memory management subsystem architecture and explores various properties of user-mode virtual address spaces. 
- Windows Internals, Seventh Edition, Part 1_: Pages 301-323
    - This section provides a conceptual overview of the memory subsystem and the services it provides to both user-mode and kernel-mode components.
- _Windows Internals, Seventh Edition, Part 1_: Pages 348-383
    - This section covers the structure of the virtual address space of Windows applications and the process utilized by the kernel to translate virtual addresses to physical addresses.

### Exercises

- [Shared Memory via Memory Protection Attributes](./shared-memory)

### Checks on Learning

- How does the Windows Heap Manager obtain the memory that it uses to service allocation requests?
- What is the size of a _standard_ (or _small_) virtual memory page on 64-bit Windows systems? The size of a _large_ page? The size of a _huge_ page? 
- Suppose one has access to a system running 64-bit Windows 8. What is the size of the user-mode virtual address space of a 64-bit executable running on this system in the event that the executable is built with the `/LARGEADDRESSAWARE:NO` flag specified? What about when the executable is built with the `/LARGEADDRESSAWARE` flag specified?
- Suppose one has access to a system running 64-bit Windows 8.1+. What is the size of the user-mode virtual address space of a 64-bit executable running on this system in the event that the executable is built with the `/LARGEADDRESSAWARE:NO` flag specified? What about when the executable is built with the `/LARGEADDRESSAWARE` flag specified?
- What is the significance of the command `bcdedit /set increaseuserva 3072` when run on a 32-bit version of Windows? When run on a 64-bit version?
- How many distinct page states exist for virtual memory pages on Windows? What is the distinction between these page states?
- What happens in the event that one references a virtual address contained within a _reserved_ virtual memory page within the current process context?
- What happens in the event that one references a virtual address contained within a _free_ virtual memory page within the current process context?
- Windows dynamic libraries (DLLs) support sharing code among multiple processes. In the event that a dynamic library declares some global data (e.g. a global variable), how might Windows implement the expected process-local semantics for this data using the `PAGE_WRITECOPY` page protection attribute?
- Suppose one has a pointer to the base of a memory region previously allocated via a call to `VirtualAlloc()`. How would one go about updating the page protection attributes for the pages in this memory region?