## Windows System Architecture

This module provides a high-level overview of Windows system architecture - how the functionality of the operating system is partitioned among various logical components. Concepts introduced in this section will be revisited frequently throughout the remainder of this curriculum.

### Key Concepts

- Distinction between Windows user-mode process types
- Windows environment subsystems 
- The system support library and the Windows system service interface
- Distinction between Windows kernel logical components
- Windows Executive components and their major functions

### Reading Material

- _Windows Internals, Seventh Edition, Part 1_: Pages 45-99
    - This section provides a whirlwind overview of the entirety of the Windows operating system environment - from the various types of user-mode applications to the various Executive subsystems and their responsibilities.

### Checks on Learning

- What type of user-mode process is an instance of `notepad.exe`?
- What type of user-mode process is an instance of `services.exe`?
- What type of user-mode process is an instance of `csrss.exe`?
- What type of user-mode process is an instance of `svchost.exe`?
- To which subsystem is an instance of the Session Manager Subsystem process (`smss.exe`) bound?
- To which subsystem is an instance of the CMD shell process (`cmd.exe`) bound?
- Which library comprises the system call interface on Windows?
- What is the system service dispatcher code for `NtWriteFile()` (`ZwWriteFile()`) on your version of Windows?
- Which Executive component is responsible for managing the Windows Registry?
- Which Executive component(s) comprise the IO subsystem? 