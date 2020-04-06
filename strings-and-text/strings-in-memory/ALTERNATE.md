## Examining Strings in Memory - Alternative Exercise (C++)

This exercise is an alternative version of the primary exercise that presents some C++-specific implementation details that arise when working with strings.

### Procedure

Build the provided executable `strings.cpp`:

```
cl /EHsc /nologo /std:c++17 /W4 strings.cpp /link /DEBUG
```

The final portion of the command above, `/link /DEBUG` passes the `/DEBUG` flag to the linker, instructing the linker to output debug symbols in a program database (.pdb) file with the build.

Once the program is built, fire up your favorite Windows debugger, be it vanilla WinDbg, WinDbg Preview, cdb, etc. For this exercise, the debugger need only be capable of user-mode debugging. Once the debugger is started, launch the executable `strings.exe` under the debugger. In WinDbg or WinDbg Preview, this may be accomplished by selecting the _Launch Executable_ option from the _File_ menu. 

When the program is launched under the debugger, the debugger breaks at the initial loader breakpoint. Use the `g` command to continue program execution. The program will subsequently break at a manually-inserted breakpoint within the program's `main()` function.

```
0:000> g
(2bb8.3888): Break instruction exception - code 80000003 (first chance)
strings!main+0x4:
00007ff6`33976c44 cc              int     3
```

Here we will begin single-stepping though the program to exercise fine-grained control. 

Using the `u` command to unassemble the current instruction stream reveals the location of the call to the first string constructor.

```
0:000> u
strings!main+0x4:
00007ff6`33976c44 cc              int     3
00007ff6`33976c45 4c8d05c4620600  lea     r8,[strings!__xt_z+0x110 (00007ff6`339dcf10)]
00007ff6`33976c4c ba00010000      mov     edx,100h
00007ff6`33976c51 488d4c2428      lea     rcx,[rsp+28h]
00007ff6`33976c56 e8d4c9ffff      call    strings!ILT+9770(??0stringQEAA_KPEBDZ) (00007ff6`3397362f)
```

Single step program execution up to the `call` instruction with either `t` or `p`, then step over the `call` with `p`.

```
0:000> p
strings!main+0x16:
00007ff6`33976c56 e8d4c9ffff      call    strings!ILT+9770(??0stringQEAA_KPEBDZ) (00007ff6`3397362f)
0:000> p
strings!main+0x1b:
00007ff6`33976c5b 90              nop
```

The return value of the constructor is now stored in the local variable on the stack of the `main()` function. The constructor returns this value in the `rax` register. Use the `r` command to dump the value in `rax`.

```
0:000> r rax
rax=0000000a844ffc08
```

Record this value as we will need it later. Next, perform the same sequence of steps for the wide string. Unassembling the current instruction stream again reveals that the wide string constructor will be invoked in short order.

```
0:000> u
strings!main+0x1b:
00007ff6`33976c5b 90              nop
00007ff6`33976c5c 4c8d05bd620600  lea     r8,[strings!__xt_z+0x120 (00007ff6`339dcf20)]
00007ff6`33976c63 ba00010000      mov     edx,100h
00007ff6`33976c68 488d4c2420      lea     rcx,[rsp+20h]
00007ff6`33976c6d e8ccb0ffff      call    strings!ILT+3385(??0wstringQEAA_KPEB_WZ) (00007ff6`33971d3e)
```

Again, single step up to the `call` instruction with either `t` or `p` and subsequently step over the `call` with `p`. Dump the return value from the wide string constructor with `r` once again.

```
0:000> r rax
rax=0000000a844ffc00
```

We now have the address of the start of both the standard string and the wide string on the stack of the `main()` function. We can now use these addresses to locate the raw memory buffers in which the strings are stored. 

The sole member of both the string and wide string structures is the address of the start of the raw string buffer on the heap. Therefore, we can use the `dq` command to dump this address from the structure start addresses on the stack.

For the standard string structure:

```
0:000> dq /c1 0000000a844ffc08
0000000a`844ffc08  00000116`0b428600
...
```

And similarly for the wide string structure:

```
0:000> dq /c1 0000000a844ffc00
0000000a`844ffc00  00000116`0b429450
...
```

Finally, we can use these two addresses to dump the raw string buffers with `db`.

For the standard string:

```
0:000> db 00000116`0b428600
00000116`0b428600  68 65 6c 6c 6f 20 77 6f-72 6c 64 00 00 00 00 00  hello world.....
00000116`0b428610  00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00  ................
```

And similarly for the wide string:

```
0:000> db 00000116`0b429450
00000116`0b429450  68 00 65 00 6c 00 6c 00-6f 00 20 00 77 00 6f 00  h.e.l.l.o. .w.o.
00000116`0b429460  72 00 6c 00 64 00 00 00-00 00 00 00 00 00 00 00  r.l.d...........
```

The difference between the in-memory representation of these two string types is immediately apparent.

The `du` command can be used to display unicode strings in a more readily-readable format:

```
0:000> du 00000116`0b429450
00000116`0b429450  "hello world"
```