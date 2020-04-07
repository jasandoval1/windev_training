## Windows Processes and the Process Management API

This module provides both a conceptual introduction to Windows processes as well as a practical overview of the process management API exposed by Win32.

### Key Concepts

- Distinction between the *nix and Windows notion of processes and process environments
- Distinction between Windows process types
- Process creation
- Process termination
- Process enumeration functions

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

### Exercises

- [Enumerating Process](./process-enumeration)

### Checks on Learning

- Among what are typically considered "normal" user-mode processes, there remain important distinctions between Windows process types. What are the five (5) distinct types of user-mode processes?
- What is the user-mode process management object? 
- What is the primary Win32 API function used to spawn new Windows processes?
- Suppose _Process A_ creates _Process B_. What is the final step in process initialization performed in the context of _Process A_?
- Suppose _Process A_ creates _Process B_. What is the first step in process initialization performed in the context of _Process B_?
- What are the four (4) application entry point functions that developers may define (excluding any generic character considerations), and the corresponding C/C++ Runtime functions that invoke these entry points on process startup?
- What are the three (3) primary conditions under which a Windows process terminates?
- What are three (3) (there may be more...) ways in which one may enumerate processes running on a Windows system?