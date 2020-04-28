## Windows Kernel Objects and Handles

This section provides both the conceptual background regarding how Windows manages system resources in the context of a uniform object model as well as the practical knowledge necessary to work effectively with kernel objects from user-mode applications.

### Key Concepts

- Windows resource management and kernel objects
- Object manipulation via Windows `HANDLE`s
- Creating objects
- Object names
- Sharing Windows objects

### Reading Material

- _Windows Via C/C++, Fifth Edition_: Pages 33-67
    - This section describes the manner in which Windows manages system resources via kernel objects and the way in which user-mode applications can manipulate these kernel objects through the abstraction provided by handles. 
- _Windows 10 System Programming_: "Objects and Handles"
    - This section provides a pragmatic overview of kernel objects and how they may be managed via the Win32 API.
- _Windows Internals, Sixth Edition, Part 1_: Pages 140-176
    - This section provides the conceptual background necessary to understand the Windows Object Manager and the role it plays in both resource management and security. 

### Exercises

- [Sharing Handles: Named Objects](./sharing-named)
- [Sharing Handles: Inheritance](./sharing-inheritance)
- [Sharing Handles: Handle Duplication](./sharing-duplication)
- [Application Single Instancing via Named Kernel Objects](./single-instancing)
- [Exploring the Process Handle Table](./handle-table)

### Checks on Learning

- What is the underlying type for a Windows `HANDLE`? Why is this type appropriate?
- The Object Manager maintains two (2) distinct reference counts for each kernel object. What are these two reference counts, and what is the distinction between them?
- Which kernel object(s) could be utilized to single-instance a program?
- When user-mode process acquires a `HANDLE` to a kernel object, it typically must specify an access mask that defines the power of that particular handle to manipulate the object to which it refers. Where is this access mask maintained for the `HANDLE`?
- Is this process handle table for a particular process stored in user virtual address space or kernel virtual address space?
- What are three (3) ways in which kernel object handles may be shared between processes?

