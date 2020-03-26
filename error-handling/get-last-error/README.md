## Exercise: `GetLastError()` Internals

This exercise will explore the implementation of the Win32 error-management facility `GetLastError()`.

### Procedure

Build the provided exercise executable, `last_error.cpp`:

```
cl /EHsc /nologo /std:c++17 /W4 last_error.cpp
```

Start an instance of your favorite Windows debugger, be it vanilla WinDbg, WinDbg Preview, cdb.exe, etc. For this exercise, the debugger need only be capable of user-mode debugging. Once the debugger is started, launch the executable `last_error.exe` under the debugger. For instance, with `cdb.exe`:

```
cdb.exe last_error.exe
```

In WinDbg or WinDbg preview, simply select the _Launch Executable_ option.

Once the program is launched under the debugger, the debugger should break on the initial process startup breakpoint.

```
(d9c.252c): Break instruction exception - code 80000003 (first chance)
ntdll!LdrpDoDebuggerBreak+0x30:
00007fff`4d21121c cc              int     3
```

We are not interested in this breakpoint, so use the `g` command to resume execution. At this point, the debugger should yield control to the program as it prompts for input. Enter an error code value. Valid values are in the range 0 to the maximum value representable within a 32-bit unsigned integer.

Once you have entered a value and pressed ENTER, the program resumes. Assuming the input is valid, the program should echo the value entered and subsequently print the value returned by a call to `GetLastError()`, which should match the value entered. 

```
0:000> g
[+] Enter error code (q to quit): 1337
[+] Setting last error to: 1337
[+] GetLastError() returns: 1337
```

Finally, the program manually triggers a break into the debugger. In the debugger, use the `!teb` command to examine the current state of the active thread's Thread Environment Block (TEB). Because there is only a single thread in this program, the active thread is the same one on which we called `SetLastError()` to manually specify the error code. Examine the contents of the TEB and verify that the contents of the `LastErrorValue` field match the expected value.

```
(d9c.252c): Break instruction exception - code 80000003 (first chance)
last_error+0x1313:
00007ff7`996d1313 cc              int     3
0:000> !teb
TEB at 000000e191380000
    ExceptionList:        0000000000000000
    StackBase:            000000e191170000
    StackLimit:           000000e19116d000
    SubSystemTib:         0000000000000000
    FiberData:            0000000000001e00
    ArbitraryUserPointer: 0000000000000000
    Self:                 000000e191380000
    EnvironmentPointer:   0000000000000000
    ClientId:             0000000000000d9c . 000000000000252c
    RpcHandle:            0000000000000000
    Tls Storage:          000000e191380058
    PEB Address:          000000e19137f000
    LastErrorValue:       1337
    LastStatusValue:      c00700bb
    Count Owned Locks:    0
    HardErrorMode:        0
```