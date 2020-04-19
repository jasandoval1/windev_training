## The Windows Security Model and Programming Windows Security

This module provides and overview of the Windows security model - how the Windows operating system defines and enforces security boundaries. Additionally, it introduces the rich API exposed by Win32 for interacting with the Windows security subsystem.

### Key Concepts

- The Windows security model
- The Windows Security Reference Monitor (SRM)
- Access Tokens and related APIs
- Security Descriptors and related APIs
- Security Identifiers (SIDs) and related APIs
- Integrity Levels and Mandatory Integrity Checks
- Account Rights and Privileges
- The Windows security model access control algorithm 

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 519-544
    - This section provides a superficial introduction to object security and the Win32 functions used to manage object security at a low level. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 608-611
    - This short section provides an overview of the major components of the security subsystem.
- _Windows Internals, Seventh Edition, Part 1_: 619-666, 668-684
    - These extremely important sections introduce the Windows security model, emphasizing the interaction between object security descriptors, process and thread access tokens, and the algorithm utilized by the security reference monitor (SRM) to determine if object access is permitted or denied. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 710-722
    - This section introduces the procedure utilized during logon to authenticate users on Windows systems.
- _Windows Internals, Seventh Edition, Part 1_: Pages 722-735
    - This section introduces the user account control (UAC) security mechanism and the procedures underlying privilege elevation.

### Checks on Learning

- Which Windows objects may be protected under the Windows object security model? (don't list them all - be concise!)
- How does Windows identify the security context of a process or thread?
- How does Windows identify the security context of a securable object?
- What is the difference between a _primary token_ and an _impersonation token_?
- Is it possible for the security context of a thread to gain credentials or privileges via impersonation?
- What roles does the Discretionary Access Control List (DACL) of an object's Security Descriptor play in implementing object security?
- What roles does the System Access Control List (SACL) of an object's Security Descriptor play in implementing object security?
- Is the order of Access Control Entries (ACEs) in a Security Descriptor's DACL relevant to access control checks?
- For what purpose does Windows use Security Identifiers? 
- How is the integrity level for an access token implemented?
- What is the default (implicit) integrity level for Windows objects?
- What are the three (3) inputs to the Security Reference Monitor's `SeAccessCheck()` function that allow it to compute whether or not the requested operation is permitted or denied?
- What is the difference between an _account right_ and a _privilege_ in the context of the Windows security model?
- Where are the privileges for a process' security context maintained?
- Suppose that a program you wrote is running in some security context that, for the purposes of this question, cannot be altered. Further, suppose that your program must perform a write operation on some secured object to which it is currenty denied access. Assuming that your program has the ability to modify the target object's security descriptor, what actions should your program take to grant itself access to the object?
- Suppose that a program you wrote is running in some security context. Further, suppose that your program must perform a write operation on some secured object to which it is currently denied access and the object's security descriptor is similarly inaccessible. Assuming that your program has the ability to modify its own security context, what actions should your program take to grant itself access to the object?
