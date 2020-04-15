## Sharing Handles: Inheritance

This exercise presents another strategy for sharing `HANDLE`s across process boundaries - sharing via handle inheritance.

### Background

Windows and the Win32 API support a variety of mechanisms for sharing references to kernel objects across process boundaries. The previous exercise looked at using kernel object names to facilitate handle sharing, but this strategy has some fundamental limitations. What if we want to create our kernel object without a name, or the specific kernel object we want to share doesn't support explicit naming? This exercise examines another strategy for sharing kernel object handles wherein a _parent_ process shares on or more of its open kernel object handles with a _child_ process that it creates.

In certain situations, sharing handles via inheritance can overcome some of the limitations imposed by sharing via kernel object names; handles shared via inheritance need to refer to named kernel objects. At the same time, however, it imposes the new limitation that the process that wants to share its handles must explicitly create the process with which it intends to do so.

### Procedure

Your task in this exercise is to implement a pair of programs that demonstrate handle sharing via inheritance. Specifically, your implementation should consist of a _parent_ process that uses the Win32 `CreateProcess()` function to spawn a _child_ process with which it shares a handle to a kernel object.

The parent process should perform the following steps:

- Create an unnamed event kernel object
- Spawn a child process with `CreateProcess()`
- Signal the unnamed event object
- Wait for the child process to terminate
- Cleanup and exit

Accordingly, the child process should perform the following steps:

- Acquire a handle to the unnamed event object
- Wait for the named event object to become signaled
- Cleanup and exit

This division of responsibility between the parent and child processes ensures that the child process will not exit unless a handle to the same named event created by the parent is acquired; thus, if the sharing of the event object is not performed correctly, both processes will hang indefinitely.

One complication that arises when sharing handles via inheritance is the fact that while the child process possesses the handle that has been shared with it, it does not immediately know how to interact with this handle. When the parent process creates a new kernel object with support for inheritance and subsequently shares this handle with a child process via the call to `CreateProcess()`, this merely inserts an entry into the child process' process-local handle table that refers to the same underlying kernel object as the parent's original handle. Importantly, the handle table index that refers to the underlying kernel object is the same in both the parent and child processes. However, how does the child process determine _which_ handle table entry refers to the shared kernel object?

This is a general issue when using inheritance to share handles between processes, and there is not a single solution to the problem. What is required is some secondary, external communication channel by which the parent process may communicate the handle table index that refers to the shared kernel object to the child.

One simple solution is to take advantage of the fact that the parent process controls the commandline that is utilized to start the child process - this presents an opportunity to communicate additional information to the child at the time it is started. The Win32 functions `HandleToULong()` and `ULongToHandle()` prove useful when pursuing this strategy.

Don't feel limited by this suggestion - feel free to wrestle with this problem and formulate your own method for communicating the handle table index to the child process.

A sample implementation that meets these requirements is provided in the `reference/` directory; don't refer to the sample programs until you have attempted the exercise yourself!