## C/C++ Runtime Memory Allocations and the Heap API

This exercise examines the C/C++ runtime facilities for memory allocation and compares their implementation with the memory allocation functions provided by the Win32 API.

### Procedure 

Build the provided exercise executable, `allocate.cpp`:

```
cl /EHsc /nologo /std:c++17 /W4 allocate.cpp /link /DEBUG
```

Here we instruct the linker to output debug symbols for the executable to aid in the debugging process. Launch the program under your favorite Windows debugger. When the debugger breaks in at the initial program loader break, use the `g` command to resume execution of the program. Finally, the debugger should break in once more at a manually-defined breakpoint within the body of the program's main function.

As a cursory examination of the program's source reveals, the program consists of the `main()` function, and three supporting functions that merely allocate memory in three distinct ways:

- the `alloc_malloc()` function calls the C Runtime Library's `malloc()`
- the `alloc_new()` function calls the C++ Runtime Library's `operator new`
- the `alloc_heap()` function calls the Win32 API `HeapAlloc()` with the first argument set to the default process heap via `GetProcessHeap()`

The objective of this exercise is to take a closer look at how each of these distinct dynamic memory allocation routines work under the hood. To this end, set a breakpoint on each of the three supporting functions listed above.

```
0:000> bp allocate!alloc_malloc
0:000> bp allocate!alloc_new
0:000> bp allocate!alloc_heap
```

Finally, set one more breakpoint on the system support library's `RtlAllocateHeap()` function; this is the entry point to the operating system's internal heap API. 

```
0:000> bp ntdll!rtlallocateheap
```

Listing the breakpoints should now produce the following output:

```
0:000> bl
     0 e Disable Clear  00007ff6`7762b890     0001 (0001)  0:**** allocate!alloc_malloc
     1 e Disable Clear  00007ff6`7762b8b0     0001 (0001)  0:**** allocate!alloc_new
     2 e Disable Clear  00007ff6`7762b8e0     0001 (0001)  0:**** allocate!alloc_heap
     3 e Disable Clear  00007ff8`9f3fb870     0001 (0001)  0:**** ntdll!RtlAllocateHeap
```

At this point, we are ready to begin examining the behavior of the various memory allocation routines. First up is `malloc()`. Use the `g` command to resume execution of the program. The first breakpoint at `alloc_malloc()` should be hit immediately.

```
0:000> g
Breakpoint 0 hit
allocate!alloc_malloc:
00007ff6`7762b890 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=06100800000906ea
```

So we have reached the entry of the `alloc_malloc()` function, and we know that all this function does is call the C Runtime Library's `malloc()`. Resume execution with `g`, and we hit the next breakpoint in `RtlAllocateHeap()`.

```
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7fa70=0000000000000000
```

So `malloc()` has ended up in `RtlAllocateHeap()`. But how did we get here?

```
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000097`89f7fa68 00007ff6`77660d54 ntdll!RtlAllocateHeap
01 00000097`89f7fa70 00007ff6`7762b8a3 allocate!_malloc_base+0x44 [minkernel\crts\ucrt\src\appcrt\heap\malloc_base.cpp @ 34] 
02 00000097`89f7faa0 00007ff6`7762b91f allocate!alloc_malloc+0x13
03 00000097`89f7fad0 00007ff6`77626f04 allocate!main+0xf
04 (Inline Function) --------`-------- allocate!invoke_main+0x22 [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 78] 
05 00000097`89f7fb20 00007ff8`9e3c7bd4 allocate!__scrt_common_main_seh+0x10c [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 288] 
06 00000097`89f7fb60 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
07 00000097`89f7fb90 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

So the internal function `_malloc_base()` defined in the C Runtime Library invoked `RtlAllocateHeap()` when it actually needed to perform dynamic memory allocation. While the function is not part of the Win32 API, it is nonetheless documented on MSDN, where its signature is reported as:

```
NTSYSAPI PVOID RtlAllocateHeap(
  PVOID  HeapHandle,
  ULONG  Flags,
  SIZE_T Size
);
```

So before moving on to the next memory allocation routine, lets determine the arguments with which `RtlAllocateHeap()` was invoked. The x64 calling convention dictates that the three arguments to the function will be passed in RCX, RDX, and R8, respectively. 

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

From the function signature, we can deduce that the value in RCX, `00000267a06f0000`, is the base address of the heap from which the requested allocation will be serviced, the value in RDX, `0`, are the flags passed to the function, and the value in R8, `8`, is the requested size of the allocation, in bytes.

Now lets move on to the next allocation routine. First, disable (but don't remove) the breakpoint we set on `RtlAllocateHeap()` - the function will be invoked several more times prior to returning to our application code, and we don't want to mess around in the internals of the heap implementation for the time being.

```
0:000> bd 3
0:000> bl
     0 e Disable Clear  00007ff6`7762b890     0001 (0001)  0:**** allocate!alloc_malloc
     1 e Disable Clear  00007ff6`7762b8b0     0001 (0001)  0:**** allocate!alloc_new
     2 e Disable Clear  00007ff6`7762b8e0     0001 (0001)  0:**** allocate!alloc_heap
     3 d Enable Clear  00007ff8`9f3fb870     0001 (0001)  0:**** ntdll!RtlAllocateHeap
```

Now resume execution of the program with `g`. The next breakpoint at the start of `alloc_new()` should be hit. 

```
0:000> g
Breakpoint 1 hit
allocate!alloc_new:
00007ff6`7762b8b0 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=0000000000000008
```

So we know that C++'s analog to `malloc()`, `operator new` is about to be invoked. Re-enable the breakpoint on `RtlAllocateHeap()` and resume execution. 

```
0:000> be 3
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7fa30=0000000000000000
```

Again we end up in `RtlAllocateHeap()`. Dump the call stack again to determine the sequence of calls that got us here.

```
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000097`89f7fa28 00007ff6`77660d54 ntdll!RtlAllocateHeap
01 00000097`89f7fa30 00007ff6`776270bb allocate!_malloc_base+0x44 [minkernel\crts\ucrt\src\appcrt\heap\malloc_base.cpp @ 34] 
02 00000097`89f7fa60 00007ff6`7762b8c3 allocate!operator new+0x1f [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\heap\new_scalar.cpp @ 35] 
03 00000097`89f7fa90 00007ff6`7762b92e allocate!alloc_new+0x13
04 00000097`89f7fad0 00007ff6`77626f04 allocate!main+0x1e
05 (Inline Function) --------`-------- allocate!invoke_main+0x22 [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 78] 
06 00000097`89f7fb20 00007ff8`9e3c7bd4 allocate!__scrt_common_main_seh+0x10c [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 288] 
07 00000097`89f7fb60 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
08 00000097`89f7fb90 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

Curiously enough, the C++ Runtime Library's implementation of `operator new` appears to be a relatively shallow wrapper around the same function that `malloc()` invoked - `_malloc_base()`. 

Once again, dump the contents of RCX, RDX, and R8 to determine the arguments with which `RtlAllocateHeap()` was invoked in this instance. 

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

We see exactly the same values for the arguments that we observed in the case of `malloc()`. Once more, disable the breakpoint on `RtlAllocateHeap()` and resume execution of the program to run back to the entry to the third and final application-defined allocation wrapper function. 

```
0:000> bd 3
0:000> g
Breakpoint 2 hit
allocate!alloc_heap:
00007ff6`7762b8e0 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=0000000000000008
```

As before, re-enable the breakpoint on `RtlAllocateHeap()` and resume execution. 

```
0:000> be 3
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7faa0=0000000000000000
```

Unsurprisingly, `HeapAlloc()` leads us to `RtlAllocateHeap()` just as `malloc()` and `operator new` did. Dump the call stack to display the call chain that lead us here. 

```
0:000> k
 # Child-SP          RetAddr           Call Site
00 00000097`89f7fa98 00007ff6`7762b8ff ntdll!RtlAllocateHeap
01 00000097`89f7faa0 00007ff6`7762b93d allocate!alloc_heap+0x1f
02 00000097`89f7fad0 00007ff6`77626f04 allocate!main+0x2d
03 (Inline Function) --------`-------- allocate!invoke_main+0x22 [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 78] 
04 00000097`89f7fb20 00007ff8`9e3c7bd4 allocate!__scrt_common_main_seh+0x10c [d:\agent\_work\4\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl @ 288] 
05 00000097`89f7fb60 00007ff8`9f42ced1 KERNEL32!BaseThreadInitThunk+0x14
06 00000097`89f7fb90 00000000`00000000 ntdll!RtlUserThreadStart+0x21
```

So `HeapAlloc()` provides a shorter path to the operating system's underlying heap management routines than either `malloc()` or `operator new`. For consistency, verify that the arguments with which `RtlAllocateHeap()` was invoked in this third scenario match the arguments we have seen in the previous two. 

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

Indeed, the heap address, flags, and allocation size remain consistent. We can verify that the first argument is indeed the base address of a process heap by using the `!heap` extension command to display all of the heaps that exist in the current process.

```
0:000> !heap
        Heap Address      NT/Segment Heap

         267a06f0000              NT Heap
         267a0530000              NT Heap
```

The argument passed as the first parameter to `RtlAllocateHeap()` in all three instances matches the address of the first heap listed in the table above. Because `HeapAlloc()` in the application source is invoked with `GetProcessHeap()`, we can determine that this heap is the default process heap, and thus that both `malloc()` and `operator new` utilize the default process heap to perform memory allocations.

This exercise has demonstrated that while the interface presented by the various memory allocation routines available to user-mode applications differ significantly, they all utilize the same underlying operating system functionality - the Windows heap - to service requests for dynamic memory allocations.
