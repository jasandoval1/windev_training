## Process Management with Jobs: UI Limitations

This exercise introduces you to the process management power of Windows jobs through one of the more straightforward limitations that jobs may impose: process clipboard access.

### Procedure

Write a program that restricts the ability of a specified process to read from the clipboard using Windows jobs. The target process should be configurable via a commandline argument. Upon successful execution of your program, the target process should no longer have the ability to read from the clipboard; for example, it should be impossible to paste text into the editor window of an instance of `notepad.exe` that is successfully limited by your program.

The API for working with Windows jobs provided by Win32 is rich, but can also prove verbose and unwieldy. To get started, look at the `SetInformationJobObject()` function and the various job object information class (`JOBOBJECTINFOCLASS`) values that it accepts.

Another important consideration here are the precise permissions required to add a specified process to a job object that you create. What are the minimum necessary permissions with which a handle to a process must be acquired in order to subsequently add it to a job? Is it possible to acquire a handle with these permissions under all circumstances?

A sample application that meets the requirements of this exercise is provided in the `reference/` directory; don't refer to it until you have attempted to exercise yourself! The reference implementation limits both read and write access to the clipboard, and accepts an arbitrary number of target process PIDs; this functionality is not required for your implementation.