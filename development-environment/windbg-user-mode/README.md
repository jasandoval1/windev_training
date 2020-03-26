## User Mode Debugging Essentials with WinDbg

This exercise walks you through the essentials of user-mode application debugging with WinDbg and WinDbg Preview.

### Procedure

In general, there are two approaches to initiate a debugging session in user mode: attaching to a running process or launching an executable from within the debugger. For the purposes of this tutorial, we will pursue the latter option, but aside from the very first steps, the two methods are identical.

Launch the debugger - for this exercise, use either WinDbg or WinDbg Preview. While the UI for these two debuggers are quite distinct, the underlying debugging engine is identical.

Once the debugger is launched, navigate to the _File_ menu and select _Launch Executable_. From the finder window that appears, navigate to the executable for Notepad - typically located at _C:\Windows\System32\notepad.exe_ - and select it. The debugger will launch the executable, and subsequently break into the process at the initial loader breakpoint. This is a pre-established point in the process lifecycle at which the Windows Image Loader checks to determine if the process is running in the context of a debugger and, if it is, yields control to the debugger. 

Use the `g` command to return control to the application so that Notepad can complete its initialization.

```
g
```

Upon entering the `g` command you should observe a number of module load actions - these are notifications for each of the dynamic libraries that Notepad has loaded. 

```
0:000> g
ModLoad: 00007ff8`9ea40000 00007ff8`9ea6e000   C:\WINDOWS\System32\IMM32.DLL
ModLoad: 00007ff8`9c2b0000 00007ff8`9c2c1000   C:\WINDOWS\System32\kernel.appcore.dll
ModLoad: 00007ff8`9a1d0000 00007ff8`9a269000   C:\WINDOWS\system32\uxtheme.dll
ModLoad: 00007ff8`9f2d0000 00007ff8`9f372000   C:\WINDOWS\System32\clbcatq.dll
...
```

At this point the application is still running. Break into the application by pressing the _Break_ button in the debugger's UI. This forces the application to break and yields control to the debugger.

```
(3c4c.5e40): Break instruction exception - code 80000003 (first chance)
ntdll!DbgBreakPoint:
00007ff8`9f45faf0 cc              int     3
```

The next command we'll look at is the `~` command which lists all threads in the current process context.

```
0:001> ~
   0  Id: 3c4c.57e8 Suspend: 1 Teb: 00000053`3d73e000 Unfrozen
.  1  Id: 3c4c.5e40 Suspend: 1 Teb: 00000053`3d74c000 Unfrozen
   4  Id: 3c4c.4b40 Suspend: 1 Teb: 00000053`3d746000 Unfrozen
   5  Id: 3c4c.6b08 Suspend: 1 Teb: 00000053`3d748000 Unfrozen
   6  Id: 3c4c.6350 Suspend: 1 Teb: 00000053`3d74a000 Unfrozen
```

Notice that one of the threads in the list above has a `.` in front of its index (the thread at index 1 in the above output); this denotes that this is the currently active thread, implying that all thread-specific operations will apply to this thread. For instance, the `k` command dumps a stack trace for the currently active thread.

```
0:001> k
 # Child-SP          RetAddr           Call Site
00 00000053`3d8ffb98 00007ff8`9f48d51b ntdll!DbgBreakPoint
01 00000053`3d8ffba0 00007ff8`9e3c7bd4 ntdll!DbgUiRemoteBreakin+0x4b
02 00000053`3d8ffbd0 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
03 00000053`3d8ffc00 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

The output shows the stack trace for the current thread, with the most proximate function context at the top of the output and the least at the bottom. The syntax for the _Call Site_ column is `ModuleName!FunctionName+Offset`. Thus, the current thread started its life in the `RtlUserThreadStart()` function within `ntdll`, which subsequently called the `BaseThreadInitThunk()` function in `KERNEL32`, and so on up the call stack until `DbgBreakPoint()` was hit, which was responsible for the break into the debugger.

As an aside, this call stack demonstrates exactly how the debugger forced a break in the debugged application - the debugger injected this thread into Notepad with the sole purpose of invoking `DbgBreakPoint()` which issued an `int 3` instruction to trigger a call to the debug exception handler, etc.

We can switch to a different thread with the `~ns` command where `n` is the index of the thread in the list of threads we saw before. For instance, to switch to the thread at index 0:

```
0:001> ~0s
win32u!NtUserGetMessage+0x14:
00007ff8`9d441164 c3              ret
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000053`3d87fb18 00007ff8`9e233a4d win32u!NtUserGetMessage+0x14
01 00000053`3d87fb20 00007ff6`9502a3e3 USER32!GetMessageW+0x2d
02 00000053`3d87fb80 00007ff6`950402c7 notepad!WinMain+0x293
03 00000053`3d87fc50 00007ff8`9e3c7bd4 notepad!__mainCRTStartup+0x19f
04 00000053`3d87fd10 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
05 00000053`3d87fd40 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

The debugger displays the current function context when we switch to the new thread, and we subsequently dump the stack trace for this new thread. We can immediately observe some of the similarities and differences between this thread's lifetime thus far and the thread that was injected by the debugger. The first two functions in the thread's call stacks are equivalent, implying that this is likely the common path for thread startup. However, after this point, we see that the new thread invoked `__mainCRTStartup()` - the C Runtime initialization function, after which the `WinMain()` function was invoked - the applications "real" entry point. Finally, the new thread is currently in the function context of `NtUserGetMessage()`, suggesting that this is the main UI thread of Notepad, and that it was waiting for user UI input when the debugger broke in. 

Going back to the output of the `~` command, one of the most important pieces of information it reports is the address of the thread environment block (TEB) for each listed thread, immediately following the word "Teb:"

```
0:000> ~
.  0  Id: 3c4c.57e8 Suspend: 1 Teb: 00000053`3d73e000 Unfrozen
#  1  Id: 3c4c.5e40 Suspend: 1 Teb: 00000053`3d74c000 Unfrozen
...
```

We can examine the TEB for the current thread by simply entering the `!teb` command.

```
0:000> !teb
TEB at 000000533d73e000
    ExceptionList:        0000000000000000
    StackBase:            000000533d880000
    StackLimit:           000000533d86f000
    SubSystemTib:         0000000000000000
    FiberData:            0000000000001e00
    ArbitraryUserPointer: 0000000000000000
    Self:                 000000533d73e000
    EnvironmentPointer:   0000000000000000
    ClientId:             0000000000003c4c . 00000000000057e8
    RpcHandle:            0000000000000000
    Tls Storage:          000001ef862b2390
    PEB Address:          000000533d73d000
    LastErrorValue:       0
    LastStatusValue:      c0000034
    Count Owned Locks:    0
    HardErrorMode:        0
```

Alternatively, with the TEB addresses reported by `~`, we can explicitly specify the address of the TEB we want to examine. 

```
0:000> !teb 00000053`3d74c000
TEB at 000000533d74c000
    ExceptionList:        0000000000000000
    StackBase:            000000533d900000
    StackLimit:           000000533d8fc000
    SubSystemTib:         0000000000000000
    FiberData:            0000000000001e00
    ArbitraryUserPointer: 0000000000000000
    Self:                 000000533d74c000
    EnvironmentPointer:   0000000000000000
    ClientId:             0000000000003c4c . 0000000000005e40
    RpcHandle:            0000000000000000
    Tls Storage:          0000000000000000
    PEB Address:          000000533d73d000
    LastErrorValue:       0
    LastStatusValue:      0
    Count Owned Locks:    0
    HardErrorMode:        0
```

Some of the more important fields displayed by this command include:

- _StackBase_ and _StackLimit_: the base and limit of the thread's user-mode stack
- _ClientId_: the process ID of the owning process, followed by the thread ID
- _LastErrorValue_: the last Win32 error code for the thread
- _PEB Address_: the address of the process environment block (PEB) for the thread's containing process

The `!teb` command is merely a helpful extension command (denoted by the fact that it is prefixed with a `!`) - it is simply showing some of the data available in the real TEB structure behind the scenes in an easy to read format. We can examine the entire TEB structure manually with the `dt` (display type) command.

```
0:000> dt nt!_teb
ntdll!_TEB
   +0x000 NtTib            : _NT_TIB
   +0x038 EnvironmentPointer : Ptr64 Void
   +0x040 ClientId         : _CLIENT_ID
    ...
   +0x180c WowTebOffset     : Int4B
   +0x1810 ResourceRetValue : Ptr64 Void
   +0x1818 ReservedForWdf   : Ptr64 Void
   +0x1820 ReservedForCrt   : Uint8B
   +0x1828 EffectiveContainerId : _GUID
```

The TEB is a large structure, so this command produces a large amount of output. Here, we prefixed the structure we wanted to diplay (`_teb` or `_TEB`, WinDbg is case insensitive) with `nt` which informs WinDbg that the symbol we are looking for is a kernel symbol - `nt` is simply a convenient shorthand for specifying the kernel symbols module. 

The above command merely dumped the TEB structure. If we want to display the TEB contents for a specified thread, we can specify the address of the TEB we want to view with the `dt` command.

```
0:000> dt nt!_teb 00000053`3d74c000
ntdll!_TEB
   +0x000 NtTib            : _NT_TIB
   +0x038 EnvironmentPointer : (null) 
   +0x040 ClientId         : _CLIENT_ID
   +0x050 ActiveRpcHandle  : (null) 
   +0x058 ThreadLocalStoragePointer : (null) 
   +0x060 ProcessEnvironmentBlock : 0x00000053`3d73d000 _PEB
   +0x068 LastErrorValue   : 0
    ...
   +0x180c WowTebOffset     : 0n0
   +0x1810 ResourceRetValue : (null) 
   +0x1818 ReservedForWdf   : (null) 
   +0x1820 ReservedForCrt   : 0
   +0x1828 EffectiveContainerId : _GUID {00000000-0000-0000-0000-000000000000}
```

The members of the structure are now listed with their offset from the beginning of the structure, their identifier, and their value in this specific instance of the structure. For simple values, the value is listed inline, while for more complex ones (like embedded structures) the value is shown with a hyperlink. Selecting this hyperlink will expand the embedded structure. For instance, to view the contents of the thread information block (TIB) we can select the `NtTib` hyperlink.

```
0:000> dx -r1 (*((ntdll!_NT_TIB *)0x533d74c000))
(*((ntdll!_NT_TIB *)0x533d74c000))                 [Type: _NT_TIB]
    [+0x000] ExceptionList    : 0x0 [Type: _EXCEPTION_REGISTRATION_RECORD *]
    [+0x008] StackBase        : 0x533d900000 [Type: void *]
    [+0x010] StackLimit       : 0x533d8fc000 [Type: void *]
    [+0x018] SubSystemTib     : 0x0 [Type: void *]
    [+0x020] FiberData        : 0x1e00 [Type: void *]
    [+0x020] Version          : 0x1e00 [Type: unsigned long]
    [+0x028] ArbitraryUserPointer : 0x0 [Type: void *]
    [+0x030] Self             : 0x533d74c000 [Type: _NT_TIB *]
```

Now that we have a general understanding of navigating the debugger, lets start introducing breakpoints. Set a breakpoint that will fire when Notepad attempts to open a file.

```
bp kernel32!createfilew
```

Notice here that we set the breakpoint on `CreateFileW()` rather than `CreateFile()` or `CreateFileA()`. The former is merely a macro that expands to one of the other two more specific options at preprocess-time, so attempting to break on `CreateFile()` won't work at all. Breaking on `CreateFileA()` would work just fine, but it merely performs some processing on the input and invokes `CreateFileW()` under the hood, so this saves us some time. 

Now that a breakpoint is set, we can list all set breakpoints with the `bl` command.

```
0:000> bl
     0 e Disable Clear  00007ff8`9e3d2090     0001 (0001)  0:**** KERNEL32!CreateFileW
```

The breakpoint's presence in the output of this command confirms that it was set successfully. Now lets test it out. Return control to Notepad with the `g` command. Once Notepad is running again, open its UI and attempt to open an existing file with the _Open_ option and...

Nothing happens. The debugger produces some output regarding module loads, but the breakpoint is not hit. Lets try again with a second breakpoint, this time on a slightly different exported function:

```
bp kernelbase!createfilew
```

Now attempting to open a file in the Notepad dialog causes the breakpoint to be hit. 

```
0:008> g
Breakpoint 1 hit
KERNELBASE!CreateFileW:
00007ff8`9cda4290 4883ec58        sub     rsp,58h
```

The distinction between `kernel32!createfilew` and `kernelbase!createfilew` is outside the scope of this exercise, but will certainly be covered in a future exercise.

Examine the call stack of the thread on which the breakpoint was hit.

```
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000053`3d8794f8 00007ff8`9c65d012 KERNELBASE!CreateFileW
01 00000053`3d879500 00007ff8`9c65ced3 windows_storage!CCachedINIFile::Load+0x6a
...
2b 00000053`3d87fb00 00007ff6`9502a3d1 USER32!DispatchMessageWorker+0x1e2
2c 00000053`3d87fb80 00007ff6`950402c7 notepad!WinMain+0x281
2d 00000053`3d87fc50 00007ff8`9e3c7bd4 notepad!__mainCRTStartup+0x19f
2e 00000053`3d87fd10 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
2f 00000053`3d87fd40 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

One of the things we may want to inspect in the event that this were a real debugging session are the arguments to the current function call. Assuming you are on a 64-bit platform with an Intel/AMD processor, the calling convention states that the first four arguments to the call are in registers RCX, RDX, R8, R9. Because the desired file is the first argument to `CreateFileW()`, the RCX register contains a pointer to the buffer that contains the string representing the file path. Thus we can dump the contents of RCX with the `r` command and subsequently examine the contents of memory at the address we get back with `db` (display bytes).

```
0:000> r rcx
rcx=000001ef8c001da0
0:000> db 000001ef8c001da0
000001ef`8c001da0  43 00 3a 00 5c 00 55 00-73 00 65 00 72 00 73 00  C.:.\.U.s.e.r.s.
000001ef`8c001db0  5c 00 6b 00 64 00 6f 00-74 00 74 00 5c 00 44 00  \.u.s.e.r.\.D.
000001ef`8c001dc0  65 00 73 00 6b 00 74 00-6f 00 70 00 5c 00 64 00  e.s.k.t.o.p.\.d.
000001ef`8c001dd0  65 00 73 00 6b 00 74 00-6f 00 70 00 2e 00 69 00  e.s.k.t.o.p...i.
000001ef`8c001de0  6e 00 69 00 00 00 ab ab-ab ab ab ab ab ab ab ab  n.i.............
000001ef`8c001df0  ab ab ab ab ab ab ee fe-ee fe ee fe ee fe ee fe  ................
000001ef`8c001e00  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
```

Because this is `CreateFileW()`, the argument is a Unicode string. We can use the `du` command to display the Unicode string directly.

```
0:000> du 000001ef8c001da0
000001ef`8c001da0  "C:\Users\user\Desktop\desktop.i"
000001ef`8c001de0  "ni"
```

Finally, lets set one more breakpoint, this time on the system service within `NTDLL` that is invoked by `CreateFileW()` to actually do the heavy lifting of file I/O. 

```
bp ntdll!ntcreatefile
```

Now return control to the application with the `g` command. The application should break back into the debugger immediately. 

```
0:000> g
Breakpoint 3 hit
ntdll!NtCreateFile:
00007ff8`9f45cb50 4c8bd1          mov     r10,rcx
```

Check out the call stack once more.

```
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000053`3d879328 00007ff8`9cda4604 ntdll!NtCreateFile
01 00000053`3d879330 00007ff8`9cda42f6 KERNELBASE!CreateFileInternal+0x2f4
02 00000053`3d8794a0 00007ff8`9c65d012 KERNELBASE!CreateFileW+0x66
```

Now use the `u` (unassemble) command to list the next instructions that will be executed. 

```
0:000> u
ntdll!NtCreateFile:
00007ff8`9f45cb50 4c8bd1          mov     r10,rcx
00007ff8`9f45cb53 b855000000      mov     eax,55h
00007ff8`9f45cb58 f604250803fe7f01 test    byte ptr [SharedUserData+0x308 (00000000`7ffe0308)],1
00007ff8`9f45cb60 7503            jne     ntdll!NtCreateFile+0x15 (00007ff8`9f45cb65)
00007ff8`9f45cb62 0f05            syscall
00007ff8`9f45cb64 c3              ret
00007ff8`9f45cb65 cd2e            int     2Eh
00007ff8`9f45cb67 c3              ret
```

We see the `syscall` instruction which is responsible for actually performing the transition to kernel mode. Just before that we see the value `55h` being moved into the EAX register - this is the system service number for `NtCreateFile()` and is one of the system service numbers that has remained relatively stable across Windows releases. 

Single step over the next few instructions with the `p` command. We could alternatively use the `t` (trace) command to step into any function calls, but attempting to step into the `syscall` call would fail because this is a user debugging session.

Once we get to the `ret` instruction, lets check the return value prior to returning control to the application. In the X64 calling convention, the return value is stored in RAX.

```
0:000> r rax
rax=0000000000000000
```

So the system call executed successfully. Clear the existing breakpoints with `bc` followed by the breakpoint index prior to returning control to the application - the `CreateFileW()` function is called many times in succession when the _Open_ dialog of Notepad is used, so failing to clear these breakpoints will result in a long process of hitting `g` repeatedly before finally getting back to the application.

Once control is returned to Notepad, the file you selected should open successfully.

This exercise has only scratched the surface of the capabilities of user-mode debugging with WinDbg, but hopefully it has successfully demonstrated how powerful the tool is and how far proficiency with it can take you.