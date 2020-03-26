## The Windows Hypervisor and Virtualization Based Security

This section explores the deepest depths of the Windows operating system environment - the internals of the Hyper-V hypervisor - and how this (relatively) new technology is being used to enhance Windows security.

### Reading Material

- _Windows Internals, Sixth Edition, Part 1_: Pages 248-269
    - This section provides some of the only information (endorsed by Microsoft, that is) available regarding the implementation of the Hyper-V hypervisor.
- _Windows Internals, Seventh Edition, Part 1_: Pages 123-129
    - This section provides an overview of _trustlets_ - applications that run in the user-mode component of virtual trust level (VTL) 1 (i.e. isolated user mode [IUM]). 
- Windows Internals, Seventh Edition, Part 1_: Pages 768-769
    - This section provides a brief introduction to HyperGuard - the hypervisor-enabled analog to kernel patch protection.

### Optional Reading Material

- [External Video: Battle of the SKM and IUM: How Windows 10 Rewrites OS Architecture](https://www.youtube.com/watch?v=LqaWIn4y26E)
    - A Blackhat 2015 talk by the Windows guru himself - Alex Ionescu - that provides a concise overview of the implementation of virtualization-based security.