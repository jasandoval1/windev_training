## Sharing Handles: Handle Duplication

This exercise presents a final strategy for sharing `HANDLE`s across process boundaries - sharing via explicit handle duplication.

### Background

Windows and the Win32 API support a variety of mechanisms for sharing references to kernel objects across process boundaries. The previous exercise looked at using inheritance to achieve this end, but this strategy presents some obvious limitations - most notably the fact that the process that intends to share a handle must explicitly create the process with which it intends to do the sharing. What if we want to share an unnamed kernel object with a process that we do not necessarily create with a call to `CreateProcess()`? This exercise explores a mechanism by which this is possible via the Win32 `DuplicateHandle()` function.

Sharing handles via explicit handle duplication is a powerful technique - it allows us to insert arbitrary handle values into the process-local handle table of another process, effectively enabling the sharing of handles to unnamed kernel objects between unrelated processes. However, we pay for the flexibility and power of this technique with the additional complexity of its employment.

### Procedure

Your task in this exercise is to implement a pair of programs that demonstrate handle sharing via explcit handle duplication. Specifically, your implementation should consist of a _parent_ process that uses the Win32 `CreateProcess()` function to spawn a _child_ process with which it shares a handle to a kernel object.

The parent process should perform the following steps:

- Create an unnamed event kernel object
- Spawn a child process with `CreateProcess()`
- Duplicate the handle to the unnamed event object with `DuplicateHandle()`
- Signal the unnamed event object
- Wait for the child process to terminate
- Cleanup and exit

Accordingly, the child process should perform the following steps:

- Acquire a handle to the unnamed event object
- Wait for the named event object to become signaled
- Cleanup and exit

This division of responsibility between the parent and child processes ensures that the child process will not exit unless a handle to the same named event created by the parent is acquired; thus, if the sharing of the event object is not performed correctly, both processes will hang indefinitely.

The complexity of sharing handles via explicit duplication lies in communicating the appropriate handle table index to the process with which the handle is shared. As in the previous exercise regarding inheritance, we require some external communication channel through which we can inform the process receiving the duplicated handle the appropriate index at which it can access it.

As in the previous exercise, there is not a single solution to this problem - Windows and Win32 provide a variety of mechanisms for interprocess communication that may accomplish what we require here. While exploring these options, you may begin to appreciate the recursive nature of this problem - interprocess communication itself also requires sharing handles across process boundaries! This merely illustrates one of the reasons that Windows supports the various handle sharing strategies that we have seen throughout these three exercises - one strategy may be appropriate where another is not, and vice versa. For the purposes of this exercise, feel free to rely on one of the other handle sharing strategies we have seen already to establish the interprocess communication channel used to inform the receiving process of the handle table index at which it may access the duplicated handle.

A sample implementation that meets these requirements is provided in the `reference/` directory; don't refer to the sample programs until you have attempted the exercise yourself!