## The Windows Security Model and Programming Windows Security

This module provides and overview of the Windows security model - how the Windows operating system defines and enforces security boundaries. Additionally, it introduces the rich API exposed by Win32 for interacting with the Windows security subsystem.

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 519-544
    - This section provides a superficial introduction to object security and the Win32 functions used to manage object security at a low level. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 608-611
    - This short section provides an overview of the major components of the security subsystem.
- _Windows Internals, Seventh Edition, Part 1_: 619-666, 668-684
    - These extremely important sections introduce the Windows security model, emphasizing the interaction between object security descriptors, process and thread access tokens, and the algorithm utilized by the security reference monitor (SRM) to determine if object access is permitted or denied. 
- _Windows Internals, Seventh Edition, Part 1_: Pages 710-722
    - This section introduces the procedure utilized during logon to authenticate users of Windows systems.
- _Windows Internals, Seventh Edition, Part 1_: Pages 722-735
    - This section introduces the user account control (UAC) security mechanism and the procedures underlying privilege elevation.