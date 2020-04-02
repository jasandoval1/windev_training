## Examining Strings in Memory

This exercise will walk you through examining the in-memory structure of the different string types available on Windows.

### Procedure

Build the provided executable `strings.c`:

```
cl /nologo /W4 strings.c /link /DEBUG
```

The final portion of the command above, `/link /DEBUG` passes the `/DEBUG` flag to the linker, instructing the linker to output debug symbols in a program database (.pdb) file with the build.

Once the program is built, fire up your favorite Windows debugger, be it vanilla WinDbg, WinDbg Preview, cdb, etc. For this exercise, the debugger need only be capable of user-mode debugging. Once the debugger is started, launch the executable `strings.exe` under the debugger. In WinDbg or WinDbg Preview, this may be accomplished by selecting the _Launch Executable_ option from the _File_ menu. 

When the program is launched under the debugger, the debugger breaks at the initial loader breakpoint. Use the `g` command to continue program execution. The program will subsequently break at a manually-inserted breakpoint within the program's `main()` function.

```
0:000> g
(6ddc.9508): Break instruction exception - code 80000003 (first chance)
strings!main+0x4:
00007ff6`92146b94 cc              int     3
```

Reviewing the source of `strings.c` reveals the overall layout of the program:

- Allocate some memory on the heap for both an ANSI string and a Unicode string
- Copy text to the allocated memory regions
- Free the allocated memory

In order to examine the structure of the strings in memory, we need the acquire the address of the location on the heap where the string buffers are located; this is why we have broken into the the program prior to the allocations. 

There are many ways we could advance through the program's execution and retrieve the address returned by the dynamic memory allocation routines (in this case, `HeapAlloc()`), but for the purposes of this exercise, we are going to keep it as simple as possible. Use the `u` command to unassemble the program's instruction sequence, we can see the location at which the first call to `HeapAlloc()` is made. Single-step to the location of this call (using either `t` or `p`) and subsequently step over (`p`) the call to `HeapAlloc()`. The MSVC x64 calling convention states that scalar return values that fit into 64 bits are returned in the RAX register; `HeapAlloc()` simply returns a pointer to the allocated memory buffer, so it fits this description. Thus, immediately after the call to `HeapAlloc()`, we can retrieve the function's return value by dumping the contents of RAX:

```
0:000> r rax
rax=0000014338808600
```

Record this value as we will make use of it later. This is the address on the heap at which our string will live. We can view the current contents of memory at this location with `db` to verify that it is currently unoccupied.

```
0:000> db 0000014338808600
00000143`38808600  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808610  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808620  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808630  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808640  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808650  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808660  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808670  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
```

In a similar manner, step through and then over the next call to `HeapAlloc()` that allocates storage for our second string, and then dump the contents of RAX:

```
0:000> r rax
rax=0000014338809450
```

Now that space for the strings has been allocated, we proceed with filling the buffers with string content. The source of `strings.c` simply uses the C Runtime functions `strcpy_s()` and `wcscpy_s()` to copy the ANSI and Unicode string literals to the allocated buffers, respectively. Step over these two calls, and then use dump the contents of memory at the string buffer locations with `db`.

The ANSI string appears as expected; each character is encoded as a single byte, and the string is terminated by a null character, `00`: 

```
0:000> db 0000014338808600
00000143`38808600  68 65 6c 6c 6f 20 77 6f-72 6c 64 00 0d f0 ad ba  hello world.....
00000143`38808610  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808620  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808630  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808640  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808650  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808660  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38808670  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
```

The Unicode string also displays the expected format; each character is represented by a two-byte value, with the least significant byte preceding the most significant byte in memory, and the string is terminated by a wide null character (`00 00`):

```
0:000> db 0000014338809450
00000143`38809450  68 00 65 00 6c 00 6c 00-6f 00 20 00 77 00 6f 00  h.e.l.l.o. .w.o.
00000143`38809460  72 00 6c 00 64 00 00 00-0d f0 ad ba 0d f0 ad ba  r.l.d...........
00000143`38809470  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38809480  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`38809490  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`388094a0  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`388094b0  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
00000143`388094c0  0d f0 ad ba 0d f0 ad ba-0d f0 ad ba 0d f0 ad ba  ................
```

Windows debuggers also include the `du` command that allows us to display the contents of a Unicode string in a more human-readable format. 

```
0:000> du 0000014338809450
00000143`38809450  "hello world"
```