## Memory Management: the Heap Manager and the Heap API

This module picks up where the previous module left off by digging into the details of a single component of the Windows memory management architecture - the Heap Manager - and the API exposed by Win32 for interacting with it.

### Key Concepts

- Windows Heap Manager architecture
- The Win32 Heap Manager API

### Read Material

- _Windows System Programming, Fourth Edition_: Pages 134-149
    - This section gives an overview of the the Windows heap API.
- _Windows Via C/C++, Fifth Edition_: Pages 519-536
    - This section provides an in-depth treatment of the Windows heap API and explores the implications of user-defined heaps.
- _Windows Internals, Seventh Edition, Part 1_: Pages 332-347
    - This section provides the conceptual background behind the Windows heap API and the existence of multiple, distinct heap implementations available to user-mode applications. 

### Optional Reading Material

- [Channel9: Heap Manager](https://channel9.msdn.com/Shows/Going+Deep/Inside-Windows-8-Greg-Colombo-Heap-Manager)
    - A look at the internals of the updated Heap Manager implementation as well as some insight into the rationale behind the system's design. 

### Exercises

- [C/C++ Runtime Memory Allocations and the Heap API](./runtime-heaps)

### Checks on Learning

- What is the minimum allocation size supported by the Heap API on 32-bit systems? On 64-bit systems?
- With how many heaps is a standard user-mode process created? Is this number different for Universal Windows Platform (UWP) applications? 
- How does the C/C++ runtime service memory allocation requests (e.g. those made by a call to `malloc()` or `operator new`)?
- What is the Low-Fragmentation Heap (LFH) and how does it relate to the Heap Manager?
- What is the difference between the NT Heap and the Segment Heap?
- Provide two instances in which it might be beneficial to create a user-defined heap with a call to `HeapCreate()`.
