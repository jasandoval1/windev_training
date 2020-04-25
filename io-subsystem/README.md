## The Windows I/O Subsystem

This module dives into the nitty-gritty details of the Windows IO subsystem; it reveals how the IO operations that have been discussed extensively in previous modules are implemented under the hood within the Windows Executive and Kernel. Mastery of the material in this module is necessary prior to beginning exploration of the exciting world of Windows kernel development - the subject of the next module.

### Key Concepts

- The Windows IO Subsystem and its components
- The Windows (asynchronous) IO model 
- The Windows layered device driver model
- IO Request Packet (IRP)
- Interrupt Request Level (IRQL)
- Deferred Procedure Call (DPC)
- IO initiation
- IO completion
- IO cancellation

### Reading Material

- _Windows Internals, Seventh Edition, Part 1_: Pages 483-498, 510-525, 533-541
    - This series of sections covers the core components of the I/O subsystem, including the I/O Manager, interrupt request levels (IRQLs) and deferred procedure calls (DPCs), the device driver taxonomy, and the details of I/O processing, including initiation, completion, and cancellation.

### Optional Reading Material

- _Windows Internals, Seventh Edition, Part 1_: 541-546
    - This section covers the internals of Windows' IO Completion Port implementation and describes how they are able to deliver superior IO performance relative to most other user-mode-visible IO strategies.
- _Windows Internals, Seventh Edition, Part 1_: 546-552
    - This section covers IO priorities and IO-related thread priority boosts.

### Exercises

- [Tracking `IRP`s](./tracking-irps)

### Checks on Learning

- Which Windows Executive subsystems compose the IO Subsystem?
- Which system resources constitute valid targets for the `CreateFile()` (or `CreateFile2()`) function? That is, what type of Windows object must be identified by the `lpFileName` argument to these functions?
- Is IRQL a property of the Windows operating system, or the hardware on which it runs?
- How many distinct IRQL exist on Windows systems running on x86 hardware? How many distinct IRQL exist on Windows systems running on x64 hardware? 
- Why are page faults and waits on kernel dispatcher objects not supported at an IRQL of 2 (`DISPATCH_LEVEL`)?
- What is the primary reason that Interrupt Service Routines (ISRs) that must perform anything beyond very simple processing typically queue a DPC that encapsulates this requirement?
- Describe the high-level actions performed by the IO Manager when a user-mode application issues a _synchronous_ IO request.
- Describe the high-level actions performed by the IO Manager when a user-mode application issues an _asynchronous_ IO request.
- Describe the rationale behind partitioning the IRP data structure into a single primary structure and a variable number of IO Stack Location structures - how is this design decision related to the Windows layered device driver model?
- The number of IO Stack Location sub-structures present in any given IRP is variable. At what point in the lifetime of the IRP is the storage (memory) for these structures allocated, and how is the appropriate size of this allocation determined?
- How does the IO Manager track outstanding IRPs while they are active when thread-agnostic IO is not used?
- How does the IO Manager track outstanding IRPs while they are active when thread-agnostic IO is used?
- How does the IO Manager implement the completion of an IO operation when thread-agnostic IO is not used?
- How does the IO Manager implement the completion of an IO operation when thread-agnostic IO is used?
- Under what conditions does the system issue a cleanup request (`IRP_MJ_CLEANUP`) against a file object?
- Under what conditions does the system issue a close request (`IRP_MJ_CLOSE`) against a file object?
- Under what conditions does the system attempt to cancel an IRP? 
- Suppose you are a malicious Windows device driver author. Assuming that some user-mode process running on your victim's system makes IO requests to a driver you control, describe how you would create an unkillable process. (Bonus: how long would this "unkillable" process remain unkillable when thread-agnostic IO is not used? When thread-agnostic IO is used?)