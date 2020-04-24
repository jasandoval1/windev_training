## System Service Dispatching 

This module covers, in a high degree of detail, the process by which user-mode applications access the services provided by the operating system. Those with a background in *NIX development will notice that the process is somewhat more complicated on the Windows platform.

### Key Concepts

- User-mode versus kernel-mode execution
- User-mode interfaces to the Windows kernel
- User-mode to kernel-mode transitions
- The Windows system call interface
- System Service Dispatch Table (SSDT)
- Hardware support for system service dispatch

### Reading Material

- _The Rootkit Arsenal, Second Edition_: Pages 130-144
    - This section provides a primer on the user-space versus kernel-space distinction as it is implemented in Windows, as well as a brief overview of Windows system architecture.
- _The Rootkit Arsenal, Second Edition_: Pages 155-174
    - This section provides an in-depth look at system service dispatching and the specifics of how it is implemented on x86/x86_64 platforms.
- _Windows Internals, Sixth Edition, Part 1_: Pages 132-140
    - This section provides a concise overview of system service dispatch.
- _Windows Internals, Sixth Edition, Part 1_: Page 225
    - This short section describes the way in which the Windows on Windows64 (WoW64) mechanism interdicts system calls and virtualizes the underlying operating system to the point that 32-bit applications may run transparently on 64-bit platforms. 

### Optional Reading Material

- _The Rootkit Arsenal, Second Edition_: Pages 514-530
    - While nominally about hooking the system service descriptor table (SSDT) as a means of interdicting system calls, this section provides an in-depth look at the internals of the SSDT. 
- [Intel Software Developer's Manual, Volume 2B: Instruction Set Reference, M-U](https://software.intel.com/en-us/download/intel-64-and-ia-32-architectures-software-developers-manual-volume-2b-instruction-set-reference-m-u) Pages 4-678 - 4-689
    - Official documentation for the `syscall`, `sysret`, `sysenter`, and `sysexit` instructions.
- [Intel Software Developer's Manual, Volume 4: Model Specific Registers](https://software.intel.com/en-us/download/intel-64-and-ia-32-architectures-software-developers-manual-volume-4-model-specific-registers) 
    - Official documentation for `IA32_LSTAR`, `IA32_SYSENTER_CS`, `IA32_SYSENTER_EIP`, and `IA32_SYSENTER_ESP` model specific registers.

### Exercises

- [Examining the SSDT](./ssdt)

### Checks on Learning

- What is the difference between the _Interrupt Descriptor Table_ and the _System Service Dispatch Table_?
- Suppose a single-threaded user-mode application invokes an API routine that requires a transition to kernel-mode execution. Does Windows execute the kernel-mode portion of this API call in a thread context that is distinct from the one that initiated the call?
- Describe the difference between a _user-mode stack_ and a _kernel-mode stack_.
- What is a _trap frame_?
- On 32-bit Intel/AMD systems, what instruction triggers a processor transition from user mode to kernel (_supervisor_) mode execution?
- On 64-bit Intel/AMD systems, what instruction triggers a processor transition from user mode to kernel mode execution?
- On 32-bit Intel/AMD systems, what instruction triggers a processor transition from kernel mode to user mode execution?
- On 64-bit Intel/AMD systems, what instruction triggers a processor transition from kernel mode to user mode execution?
- How does the processor locate the kernel mode entry point after a transition from user mode to kernel mode execution is triggered?
- Where are the routines that implement the Kernel32 API functions located within the Windows kernel?
- Where are the routines that implement the User32 and GDI32 API functions located within the Windows kernel? 
- What is the difference between native API calls prefixed with `Zw` prefix and those prefixed with `Nt` when invoked from user-mode applications
- What is the difference between native API calls prefixed with `Zw` prefix and those prefixed with `Nt` when invoked from kernel components (e.g. kernel-mode drivers)?