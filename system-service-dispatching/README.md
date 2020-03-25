## System Service Dispatching 

This module covers, to a high degree of detail, the process by which user-mode applications access the services provided by the operating system. Those with a background in *NIX development will notice that the process is somewhat more complicated on the Windows platform.

### Reading Material

- _The Rootkit Arsenal, Second Edition_: Pages 131-144
    - This section provides a primer on the user-space versus kernel-space distinction as it is implemented in Windows.
- _The Rootkit Arsenal, Second Edition_: Pages 155-174
    - This section provides an in-depth look at system service dispatching and the specifics of how it is implemented on x86/x86_64 platforms.
- _Windows Internals, Sixth Edition, Part 1_: Pages 132-140
    - This section provides a concise overview of system service dispatch.

### Optional Reading Material

- _The Rootkit Arsenal, Second Edition_: Pages 514-530
    - While nominally about hooking the system service descriptor table (SSDT) as a means of interdicting system calls, this section provides an in-depth look at the internals of the SSDT. 
