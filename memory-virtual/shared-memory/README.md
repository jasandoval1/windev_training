## Exercise: Shared Memory via Memory Protection Attributes

In this exercise you will explore how memory protection attributes control the semantics of how code and data is shared between multiple instances of executables and dynamic libraries running on the same system.

### Procedure Part 1: Baseline

In Part 1 of this exercise, you will implement a baseline program that will be used as a contrast against the program that makes use of shared memory that you will write in Part 2. 

Implement a simple application that defines some global data; it need not be anything complex, a primitive such as an integer or floating point type will suffice. With this global data defined, your program should simply define a loop that prompts for user input and subsequently modifies the global data in response to this input. For instance, if your global data is an integral or floating point type, it might simply increment the value of this global variable by 1 when the user presses ENTER. 

Once you have implemented this baseline application and verified that it works as expected, run two instances of the program simultaneously and interleave your interactions between the two instances. As you would expect, the value of the global variable in the first instance of the application does not affect the value of the global variable in the second, and vice versa - the data, while global in the context of the application, remains local to the process and is not shared across multiple instances of the executable.

A sample application that meets these requirements is provided in the `reference/` directory. Do not refer to the sample implementation until you have attempted the implementation on your own!

### Procedure Part 2: Creating a New Section

With the baseline out of the way, implement a modified your application (keep the original around) to define the global data within a new executable section of your own specification with shared memory semantics. This may be accomplished in two steps.

First, wrap the declaration and initialization of your global data in a new data section of your own specification. This is accomplished with the `data_seg` linker pragma. For instance, the source below declares and initializes a global variable `g_shared_data` to `0` within a new executable section named `shared`. 

```
#pragma data_seg("shared")
volatile unsigned long g_shared_data = 0;
#pragma data_seg()
```

Second, specify the memory protection attributes of this new section. This is accomplished via the `comment` linker pragma. For instance, the source below specifies that the section named `shared` should be readable and writeable (`RW`), and should be considered shared memory (`S`) rather than the default - copy-on-write. 

```
#pragma comment(linker, "/section:shared,RWS")
```

Build and run your modified version of the program. Once you are convinced that it still works as expected when a single instance is executed, run two instance simultaneously and interleave your interaction between the two. You should now observe that your modifications to the globally-defined data in one instance are reflected in the second instance - the memory in the new section you have defined is shared between the two processes!

One important not before we move on: we skipped over a very important implementation detail in the discussion above - thread safety. In this new implementation with shared memory, two or more threads may be concurrently accessing the same memory address when reads and writes to the global data are performed. As such, a correct, thread-safe implementation should perform writes to the global data in a thread-safe manner. This may be accomplished via atomic instructions in the event the global data is a simple integral type (e.g. via the `Interlocked` family of functions exposed by the Win32 API) or by protecting data accesses with a iter-process synchronization mechanism (e.g. a Windows mutex) in the event the data is more substantial.

A sample application that meets these requirements is provided in the `reference/` directory. Do not refer to the sample implementation until you have attempted the implementation on your own!

### Procedure Part 3: Binary Analysis

Finally, lets take a quick look at how the shared memory phenomenon we observed is implemented at the binary level. Use the `dumpbin` utility (provided in the Windows SDK) to dump the headers of the baseline implementation (without a shared memory section).

```
> dumpbin /headers private_memory.exe
Microsoft (R) COFF/PE Dumper Version 14.25.28612.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file private_memory.exe

PE signature found

File Type: EXECUTABLE IMAGE

FILE HEADER VALUES
            8664 machine (x64)
               6 number of sections
...
```

Here the output tells us that the executable has six (6) sections. At the bottom of the output, we get a summary of the names of each of these sections and their sizes.

```
...
  Summary

        3000 .data
        3000 .pdata
       15000 .rdata
        1000 .reloc
       2E000 .text
        1000 _RDATA
```

Now perform a similar analysis on the updated executable that defines its own shared memory section.

```
> dumpbin /headers shared_memory.exe
Microsoft (R) COFF/PE Dumper Version 14.25.28612.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file shared_memory.exe

PE signature found

File Type: EXECUTABLE IMAGE

FILE HEADER VALUES
            8664 machine (x64)
               7 number of sections
...
```

We see the the updated executable has seven (7) executable sections, rather than the six (6) observed in the baseline application. The summary reveals the identity of the new section.

```
...
  Summary

        3000 .data
        3000 .pdata
       15000 .rdata
        1000 .reloc
       2E000 .text
        1000 _RDATA
        1000 shared
```

A new section named `shared` appears in the output (the name of your section may vary, depending on what you named it in your program source with the linker pragma). Scrolling up a bit from the summary, we find a more detailed breakdown of our new section.

```
SECTION HEADER #5
  shared name
       4 virtual size
   4A000 virtual address (000000014004A000 to 000000014004A003)
     200 size of raw data
   46A00 file pointer to raw data (00046A00 to 00046BFF)
       0 file pointer to relocation table
       0 file pointer to line numbers
       0 number of relocations
       0 number of line numbers
D0000040 flags
         Initialized Data
         Shared
         Read Write
```

The `flags` value at the end of the output is the relevant portion here; we see that the section is defined with both `Read` and `Write` protections, and that the section is `Shared` - it is this property that enables the inter-process data sharing that we observed.

