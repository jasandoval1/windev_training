## C/C++ Runtime Memory Allocations and the Heap API

This exercise examines the C/C++ runtime facilities for memory allocation and compares their implementation with the memory allocation functions provided by the Win32 API.

### Procedure 

```
0:000> bp allocate!alloc_malloc
0:000> bp allocate!alloc_new
0:000> bp allocate!alloc_heap
0:000> bp ntdll!rtlallocateheap
0:000> bl
     0 e Disable Clear  00007ff6`7762b890     0001 (0001)  0:**** allocate!alloc_malloc
     1 e Disable Clear  00007ff6`7762b8b0     0001 (0001)  0:**** allocate!alloc_new
     2 e Disable Clear  00007ff6`7762b8e0     0001 (0001)  0:**** allocate!alloc_heap
     3 e Disable Clear  00007ff8`9f3fb870     0001 (0001)  0:**** ntdll!RtlAllocateHeap
```

```
0:000> g
Breakpoint 0 hit
allocate!alloc_malloc:
00007ff6`7762b890 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=06100800000906ea
```

```
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7fa70=0000000000000000
```

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

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

```
0:000> bd 3
0:000> bl
     0 e Disable Clear  00007ff6`7762b890     0001 (0001)  0:**** allocate!alloc_malloc
     1 e Disable Clear  00007ff6`7762b8b0     0001 (0001)  0:**** allocate!alloc_new
     2 e Disable Clear  00007ff6`7762b8e0     0001 (0001)  0:**** allocate!alloc_heap
     3 d Enable Clear  00007ff8`9f3fb870     0001 (0001)  0:**** ntdll!RtlAllocateHeap
```

```
0:000> g
Breakpoint 1 hit
allocate!alloc_new:
00007ff6`7762b8b0 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=0000000000000008
```

```
0:000> be 3
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7fa30=0000000000000000
```

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

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

```
0:000> bd 3
0:000> g
Breakpoint 2 hit
allocate!alloc_heap:
00007ff6`7762b8e0 48894c2408      mov     qword ptr [rsp+8],rcx ss:00000097`89f7fad0=0000000000000008
```

```
0:000> be 3
0:000> g
Breakpoint 3 hit
ntdll!RtlAllocateHeap:
00007ff8`9f3fb870 48895c2408      mov     qword ptr [rsp+8],rbx ss:00000097`89f7faa0=0000000000000000
```

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

```
0:000> r rcx
rcx=00000267a06f0000
0:000> r rdx
rdx=0000000000000000
0:000> r r8
r8=0000000000000008
```

```
0:000> !heap
        Heap Address      NT/Segment Heap

         267a06f0000              NT Heap
         267a0530000              NT Heap
```
