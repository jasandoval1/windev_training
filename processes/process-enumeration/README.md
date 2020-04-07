## Exercise: Enumerating Processes

This exercise explores some of the mechanisms that Windows provides for enumerating processes.

### Procedure

Write a program that enumerates the running processes on the system on which it is executed using (at least) three distinct methods. The method of process enumeration should be determined at the time the program is executed via a commandline argument. After enumerating the currently active processes, the program should write some details regarding the processes it has enumerated to its standard output.

There are many distinct ways to enumerate active processes on a Windows system. Three functions that may help to get you started are:

- `EnumProcesses()`
- `CreateToolhelp32Snapshot()`
- `WTSEnumerateProcesses()`

While researching the various enumeration methods, you will find that each offers distinct tradeoffs between, for instance, the limitations on the processes they can and cannot enumerate, the complexity of their employment, the degree of information they provide, etc. Noticing and understanding these tradeoffs is an important component of this exercise.

A sample application that meets these requirements is provided in the `reference/` directory; don't refer to it until you have attempted the exercise yourself!

### Extra Credit

Write a program that enumerates processes using the native API directly. This approach requires slightly more work on both the enumeration side and on the processing of the results, but you are rewarded with the highest level of detail available for process enumeration from userspace.

A sample application that enumerates processes using only the native API is provided in the `reference/` directory.