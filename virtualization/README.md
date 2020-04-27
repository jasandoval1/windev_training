## The Windows Hypervisor and Virtualization Based Security

This section explores the deepest depths of the Windows operating system environment - the internals of the Hyper-V hypervisor - and how this (relatively) new technology is being used to enhance Windows security.

### Key Concepts

- Virtual Trust Level (VTL)
- Virtual Trust Levels versus hardware privilege levels
- Execution environments introduced by Virtualization Based Security (VBS)
    - Secure Kernel Mode (SKM)
    - Isolated User Mode (IUM)
- Virtualization Based Security components
    - Credential Guard
    - Device Guard
    - HyperVisor Code Integrity (HVCI)
    - HyperGuard

### Reading Material

- _Windows Internals, Sixth Edition, Part 1_: Pages 248-269
    - This section provides some of the only information (endorsed by Microsoft, that is) available regarding the implementation of the Hyper-V hypervisor.
- _Windows Internals, Seventh Edition, Part 1_: Pages 59-61
    - This section provides an overview of the system architecture changes introduced by Virtualization Based Security.
- _Windows Internals, Seventh Edition, Part 1_: Pages 123-129
    - This section provides an overview of _trustlets_ - applications that run in the user-mode component of virtual trust level (VTL) 1 (i.e. isolated user mode [IUM]). 
- _Windows Internals, Seventh Edition, Part 1_: Pages 611-619
    - This section introduces some of the features of _Credential Guard_ and _Device Guard_ - two security features enabled by the hypervisor and the Virtualization Based Security components most often touted by Microsoft.
- Windows Internals, Seventh Edition, Part 1_: Pages 768-769
    - This section provides a brief introduction to HyperGuard - the hypervisor-enabled analog to kernel patch protection.

### Optional Reading Material

- [External Video: Battle of the SKM and IUM: How Windows 10 Rewrites OS Architecture](https://www.youtube.com/watch?v=LqaWIn4y26E)
    - A Blackhat 2015 talk by the Windows guru himself - Alex Ionescu - that provides a concise overview of the implementation of virtualization-based security.

### Checks on Learning

- On 86/x64 hardware, at what hardware privilege level does code executing in Secure Kernel Mode execute?
- On x86/x64 hardware, at what hardware privilege level does code executing the Isolated User Mode execute?
- What is the name of the `ntdll` analog that is loaded by processes that execute in Isolated User Mode?
- What is the name of the `kernelbase` analog that is loaded by processes that execute in Isolated User Mode?
- What are the two hardware capabilities that must be supported by hardware in order for VBS to function?
- What type of file is used to launch an Isolated User Mode _trustlet_?
- Is it possible for code executing in the standard (VTL 0) kernel to manipulate secure processes (trustlets) executing in Isolated User Mode at VTL 1?
- What is the mechanism by which secure processes executing in Isolated User Mode at VTL 1 may communicate with the standard (VTL 0) kernel or standard user-mode applications? 
- How does Credential Guard leverage Virtualization Based Security technology to protect user logon credentials?
- How does Device Guard, and specifically the HyperVisor Code Integrity (HVCI) feature, prevent unsigned or untrusted code from being loaded in the standard (VTL 0) kernel even in the event of kernel compromise?
- The standard Kernel Patch Protection (i.e. _PatchGuard_) security feature monitors critical kernel-mode data structures and functions for evidence of runtime modification, crashing the system in the event that such a modification is identified. PatchGuard relies on a degree of obfuscation and non-determinism in its implementation of this procedure. Why, then, does the Hypervisor-enabled analog of PatchGuard - _HyperGuard_ - not place a similar reliance on obfuscation and nondeterminism?