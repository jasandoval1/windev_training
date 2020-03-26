## Windows Processes and the Process Management API

This module provides both a conceptual introduction to Windows processes as well as a practical overview of the process management API exposed by Win32.

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 181- 221
    - This section provides an introduction to the Win32 process management API, as well as useful information regarding the sharing of kernel object handles between processes.
- _Windows Via C/C++, Fifth Edition_: Pages 67-124
    - This section provides an alternative look at the Win32 process management API, as well as an introduction to several aspects of Windows security as they relate to process management (elevation). Note that their is significant overlap with the previously listed resource; choose one to read as the primary and subsequently skim the other to address any content discrepancies.
- _Windows 10 System Programming_: "Processes"
    - This section provides practical examples of process creation, termination, and enumeration, as well as an overview of the distinct user-mode process types recognized by Windows.
- _Windows Internals, Seventh Edition, Part 1_: Pages 101-123, 154-155
    - These sections provide the conceptual background for Windows processes and offer a glimpse of how processes are managed by the system under the hood.

### Optional Reading Material

- _Windows Internals, Seventh Edition, Part 1_: Pages 129-154
    - This section provides the nitty-gritty details behind a call to `CreateProcess()`.
