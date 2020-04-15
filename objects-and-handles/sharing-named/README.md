## Sharing Handles: Named Objects

This exercise introduces you to the concept of sharing kernel object references (`HANDLE`s) across process boundaries via the most straightforward mechanism available - kernel object names.

### Background

Windows and the Win32 API support a variety of mechanisms for sharing references to kernel objects across process boundaries. The simplest of these mechanisms is sharing via kernel object name. Under this method, one process creates a new kernel object with some `Create*()` call and explicitly specifies the object' name; subsequently any other process may acquire a handle to the same underlying kernel object by invoking the appropriate `Create*()` or `Open*()` function with the same name specified. 

There are some limitations to this strategy for sharing references to kernel objects, one of which is the fact that only a subset of kernel objects support the assignment of names at the time of their creation. 

At the same time, however, this strategy is flexible and powerful because it does not require the processes that share kernel object handles to be related in any way - so long as one process "knows" the name of the named kernel object created by another, it can acquire a handle to the same underlying kernel object (assuming the creating process has not imposed further access control restrictions, but that's another story).

### Procedure

Your task in this exercise is to implement a pair of programs that demonstrate handle sharing via named kernel objects. Specifically, your implementation should consist of a _parent_ process that uses the Win32 `CreateProcess()` function to spawn a _child_ process with which it shares a handle to a named kernel object.

The parent process should perform the following steps:

- Create a named event kernel object
- Spawn a child process with `CreateProcess()`
- Signal the named event object
- Wait for the child process to terminate
- Cleanup and exit

Accordingly, the child process should perform the following steps:

- Acquire a handle to the named event object created by the parent process; you may assume that the name of the named event object is known ahead of time so there is no need to communicate it to the child process via some other channel (e.g. a commandline argument) - it may simply be a constant string defined in the source of both programs
- Wait for the named event object to become signaled
- Cleanup and exit

This division of responsibility between the parent and child processes ensures that the child process will not exit unless a handle to the same named event created by the parent is acquired; thus, if the sharing of the event object is not performed correctly, both processes will hang indefinitely.

A sample implementation that meets these requirements is provided in the `reference/` directory; don't refer to the sample programs until you have attempted the exercise yourself!