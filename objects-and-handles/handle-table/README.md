## Exercise: Exploring the Process Handle Table

In this exercise, we will explore some of the internals of the process handle table and the object manager.

### Background and Setup

This exercise requires a complete kernel debugging setup. If you do not have a kernel debugging environment configured, refer to the kernel debugging exercise in the `Development Environment` module for instructions on how to do this. Hereafter, host machine on which you run your kernel debugger will be referred to as the _host_ while the virtual machine in which you run the operating system instance that will be debugging will be referred to as the _debug target_.

This exercise includes an application `handle_table.cpp` that we will use during the debugging session. Build the application with the following command:

```
cl /EHsc /nologo /std:c++17 /W4 handle_table.cpp
```

and copy the resulting executable `handle_table.exe` to the debug target. Ensure that all of the necessary debugging symbols are configured and loaded on the host  (`.reload /f`). 

### Procedure

If the debugger is currently broken into the debug target, resume its execution. Execute the application, `handle_table.exe`, that you copied to the debug target. You should be presented with output similar to the following:

```
> handle_table.exe Event123
[+] Successfully created event: Event1234
[+] Handle value: 136
```

The application simply creates a new Windows event object for which we specify a name on the commandline. The name of the event need not match what is used in the example above, but it should be something recognizable so that we can visually grep for it in the kernel debugging session. The output of executing the application confirms that the event with the specified name was created successfully and also prints the raw handle value returned by the call to `CreateEvent()` in decimal form. After it creates the event, the application simply waits for user input, cleaning up and exiting when the `ENTER` key is received. 

We will use this simple application as a target for our debugging of the handle table and object manager structures. Accordingly, do not exit the application; leave it suspended where it is and break back into the debug target in the kernel debugger.

**Locating an Object Handle**

The first thing we will do is locate the event object that was created by our application. The first step in this process is to locate the process that hosts the application we just launched. The `!process` command makes this simple:

```
kd> !process 0 1 handle_table.exe
PROCESS ffff96817396c4c0
    SessionId: 1  Cid: 1514    Peb: c8b6877000  ParentCid: 170c
    DirBase: 287a4002  ObjectTable: ffffe5842266a600  HandleCount:  35.
    Image: handle_table.exe
    VadRoot ffff9681758b0520 Vads 20 Clone 0 Private 91. Modified 3. Locked 2.
    DeviceMap ffffe5841f4e8b70
```

With the address of the `EPROCESS` structure returned in the results of `!process` we can now use the `!handle` command to search for our event object in the process handle table:

```
1: kd> !handle 0 3 ffff96817396c4c0 Event

Searching for handles of type Event

PROCESS ffff96817396c4c0
    SessionId: 1  Cid: 1514    Peb: c8b6877000  ParentCid: 170c
    DirBase: 287a4002  ObjectTable: ffffe5842266a600  HandleCount:  35.
    Image: handle_table.exe

Handle table at ffffe5842266a600 with 35 entries in use

   ...

0088: Object: ffff9681758b0b30  GrantedAccess: 001f0003 Entry: ffffe58422064220
Object: ffff9681758b0b30  Type: (ffff96816e6a7c40) Event
    ObjectHeader: ffff9681758b0b00 (new version)
        HandleCount: 1  PointerCount: 2
        Directory Object: ffffe5841e4bc380  Name: Event1234
```

It appears that there are a number of event objects in the handle table for our application, but because we gave our event a name, it is easily identifiable in the complete output.

The `!handle` command provides quite a bit of useful information. A quick rundown of the various fields shown in the output above:

- `0088`: The very first value in the output is the handle table index for this entry; we can verify that this is the same value that the application produced when we initially executed it:

```
kd> ? 0x88
Evaluate expression: 136 = 00000000`00000088
```

- `Object: ffffbe0417a2cc60`: This is the address of the object itself, in this case, a `KEVENT` object.
- `GrantedAccess: 001f0003 (Protected) (Inherit)`: This is a bitmask that denotes the access rights that our process has been granted on this `HANDLE`.
- `Entry: ffff9c0731cfe220`: This is the address of the handle table entry (`HANDLE_TABLE_ENTRY`) for this handle; we will get to this structure in due course.
- `Type: (ffffbe04114b8c40) Event`: This is the address of the type object for this particular object; again, we will further explore the type object momentarily.
- `ObjectHeader: ffffbe0417a2cc30 (new version)`: This is the address of the object header (`OBJECT_HEADER`) that precedes the body of this object.
- `HandleCount: 1`: This is the number of open handles that refer to this particular object; it appears that our application has the only open handle that refers to this event.
- `PointerCount: 2`: This is the number of outstanding references for this particular object; the Object Manager only destroys an object once both its handle count and reference count drop to zero.

Ostensibly, the `!handle` command provides us with a wealth of information with which we can further explore the internals of this event object. Before we get to that, however, let's take a quick detour and look at exactly how the `!handle` command works some of its magic. Specifically, given a pointer to an `EPROCESS` structure, how do we locate a particular handle of interest within the process' handle table?

**Parsing the Raw Handle Table**

The first step in parsing the raw handle table for a process is locating the handle table itself. Once we have a pointer to the `EPROCESS` for the process of interest, we can dump the raw `EPROCESS` structure:

```
kd> dt nt!_EPROCESS ffff96817396c4c0
   +0x000 Pcb              : _KPROCESS
   ...
   +0x418 ObjectTable      : 0xffffe584`2266a600 _HANDLE_TABLE
```

The `ObjectTable` field of the `EPROCESS` structure is slightly misnamed - it is indeed the address of the process handle table. Now we can use that address and dump the raw handle table contents:

```
1: kd> dt nt!_HANDLE_TABLE 0xffffe584`2266a600
   +0x000 NextHandleNeedingPool : 0x400
   +0x004 ExtraInfoPages   : 0n0
   +0x008 TableCode        : 0xffffe584`22064000
   +0x010 QuotaProcess     : 0xffff9681`7396c4c0 _EPROCESS
   +0x018 HandleTableList  : _LIST_ENTRY [ 0xffffe584`1fd5b418 - 0xffffe584`2266a418 ]
   +0x028 UniqueProcessId  : 0x1514
   +0x02c Flags            : 0x18
   +0x02c StrictFIFO       : 0y0
   +0x02c EnableHandleExceptions : 0y0
   +0x02c Rundown          : 0y0
   +0x02c Duplicated       : 0y1
   +0x02c RaiseUMExceptionOnInvalidHandleClose : 0y1
   +0x030 HandleContentionEvent : _EX_PUSH_LOCK
   +0x038 HandleTableLock  : _EX_PUSH_LOCK
   +0x040 FreeLists        : [1] _HANDLE_TABLE_FREE_LIST
   +0x040 ActualEntry      : [32]  ""
   +0x060 DebugInfo        : (null) 
```

Nothing in this output immediately screams "here is the handle table!" Don't be mislead by the `HandleTableList` field - this is NOT a linked-list of handle table entries for all of the handles in the process (imagine how slow that would be, especially considering the indices for all handles are known ahead of time). Indeed, we need to do some work on our own to actually get to the underlying handle table and locate the entry for our event. The process for doing this is not particularly well documented; in fact, I was unable to find any documentation for this structure whatsoever when preparing this exercise. I developed the procedure below by referring to the [source for ReactOS](https://doxygen.reactos.org/de/d51/ntoskrnl_2ex_2handle_8c_source.html) and backing out the raw handle table structure from its implementation. Accordingly, take the following with a grain of salt as it is subject to change in future releases of Windows. 

The first relevant information we need to be aware of is that the `TableCode` field within the `HANDLE_TABLE` structure contains the address of the base of the raw handle table itself.

```
kd> dt nt!_HANDLE_TABLE 0xffffe584`2266a600
   ...
   +0x008 TableCode        : 0xffffe584`22064000
```

From the reading for this module, you will be familiar with the fact that recent versions of Windows implement the process handle table as a three level structure (much like the structure used to implement multi-level page tables). Thus, the first thing we need to do is determine the number of handle table levels currently in use for this process. The following computation accomplishes just that:

```
kd> ?? (ULONG)(0xffffe584`22064000 & 0x3)
ULONG 0
```

So this process is using only a single level of the handle table. This makes intuitive sense; we saw in the output from `!handle` above that there are something like 35 total handles in use for this process, so a single level of the handle table is all that is currently required.

Next, we need to calculate the actual base of the handle table, which is accomplished by simply masking off the least significant two bits of the `TableCode` value; combined with the previous step, we can conclude that the `TableCode` field specifies the address of the raw handle table, and uses its least significant two bits as flags to denote the handle table level in use.

```
1: kd> ?? 0xffffe58422064000 & (ULONGLONG)(~0x3)
unsigned int64 0xffffe584`22064000
```

So we now know the address of the raw handle table, and we know that only the first level handle table is in use. Great, the only thing left to do is determine the appropriate index into the raw handle table for the event handle in which we are interested. You might be tempted to just use the `0x88` index value we saw earlier (I know I certainly was...) but it's not quite that simple; while this value is indeed an index into the process handle table, it accounts for the fact that the handle table may have up to three levels, thus it is actually composed of multiple indicies, partitioned using the magic (horror) of C unions and bitfields. 

The structure that Windows uses internally to represent `HANDLE`s is actually something like the following:

```
 typedef union _EXHANDLE
 {
      struct
      {
          ULONG_PTR TagBits:     HANDLE_TAG_BITS;
          ULONG_PTR Index:       HANDLE_INDEX_BITS;
          ULONG_PTR KernelFlag : KERNEL_FLAG_BITS;
      };
      struct
      {
          ULONG_PTR TagBits2:    HANDLE_TAG_BITS;
          ULONG_PTR LowIndex:    HANDLE_LOW_BITS;
          ULONG_PTR MidIndex:    HANDLE_HIGH_BITS;
          ULONG_PTR HighIndex:   HANDLE_HIGH_BITS;
          ULONG_PTR KernelFlag2: KERNEL_FLAG_BITS;
      };
      HANDLE GenericHandleOverlay;
      ULONG_PTR Value;
      ULONG AsULONG;
 } EXHANDLE, *PEXHANDLE;
```

When programming in user mode, we only ever see the `HANDLE` type, represented here by the `GenericHandleOverlay` member of the union. However, internally, Windows uses the other members of this union to perform certain calculations, such as locating the handle in the raw handle table array as we are doing now. 

We identified before that only the first level of the multi-level handle table structure is in use in this process. Therefore, the field of interest in the union above is the `LowIndex` member of the anonymous `struct`. To determine the value of this field, obviously we will need to know the values of these various macros that define the width of the bitfields. Their definition is as follows:

```
 #ifdef _WIN64
 #define HANDLE_LOW_BITS (PAGE_SHIFT - 4)
 #define HANDLE_HIGH_BITS (PAGE_SHIFT - 3)
 #else
 #define HANDLE_LOW_BITS (PAGE_SHIFT - 3)
 #define HANDLE_HIGH_BITS (PAGE_SHIFT - 2)
 #endif
 #define HANDLE_TAG_BITS (2)
 #define HANDLE_INDEX_BITS (HANDLE_LOW_BITS + 2*HANDLE_HIGH_BITS)
 #define KERNEL_FLAG_BITS (sizeof(PVOID)*8 - HANDLE_INDEX_BITS - HANDLE_TAG_BITS)
```

And of course these macro definitions in turn depend on the value of `PAGE_SHIFT`:

```
 #ifndef PAGE_SHIFT
 #define PAGE_SHIFT 12
 #endif //PAGE_SHIFT
```

Thus, the layout of the 64 bits that compose our `HANDLE`, when interpreted through the lens of this anonymous structure, is the following:

```
--------------------------------------------------------------------------------
| KernelFlag2 (36) | HighIndex (9) | MidIndex (9) | LowIndex (8) | TagBits (2) |
--------------------------------------------------------------------------------
```


With this information in hand, we can now finally translate the handle value that we have to the index into the raw handle table that we need. The handle table value is `0x88` (the exact value may differ in your case, the procedure is the same though); all we need to do to isolate the value of `LowIndex` is shift right by 2 bits to get rid of the `TagBits`:

```
kd> ? 0x88>>2
Evaluate expression: 34 = 00000000`00000022
```

So we have the index into the raw handle table array. Combine that with the size of an individual handle table entry:

```
kd> ?? sizeof(nt!_HANDLE_TABLE_ENTRY)
unsigned int64 0x10
```

And we can compute the final address of the handle table entry for our event object:

```
1: kd> ? 0xffffe58422064000+0x22*0x10
Evaluate expression: -29119307431392 = ffffe584`22064220
```

Ok, looks... right? How do we check this? Just make sure it matches up with the output of `!handle`:

```
1: kd> !handle 0 3 ffff96817396c4c0 Event

Searching for handles of type Event

PROCESS ffff96817396c4c0
    SessionId: 1  Cid: 1514    Peb: c8b6877000  ParentCid: 170c
    DirBase: 287a4002  ObjectTable: ffffe5842266a600  HandleCount:  35.
    Image: handle_table.exe

Handle table at ffffe5842266a600 with 35 entries in use

   ...

0088: Object: ffff9681758b0b30  GrantedAccess: 001f0003 Entry: ffffe58422064220
Object: ffff9681758b0b30  Type: (ffff96816e6a7c40) Event
    ObjectHeader: ffff9681758b0b00 (new version)
        HandleCount: 1  PointerCount: 2
        Directory Object: ffffe5841e4bc380  Name: Event1234
```

Success!

**Locating an Object from its `HANDLE_TABLE_ENTRY`**

Alright, so we've seen how it is possible to locate the handle table entry for a specific handle of interest within the process handle table. Now what can we do once we have this handle table entry? Quite a lot, as it turns out - the process handle table entry is the gateway to all of the per-object data maintained by the Windows Object Manager. As a quick reminder, the overall structure of the per-object data maintained by the Object Manager looks something like this:

```
------------------------
      Pool Header
------------------------
   Optional Header(s)
------------------------
      Object Header
------------------------
       Object Body
------------------------
```

The pool header (`POOL_HEADER`) is simply a structure used by the kernel pool allocator to manage dynamic memory allocations, so its not particularly relevant here. The object header (`OBJECT_HEADER`) is a common header shared by all objects managed by the Object Manager. The object header may be preceded by anywhere from zero to five optional headers that provide additional information about the object (these will be covered in depth below). Finally, the object body itself is the object-specific data. For example, in our case this will be the body of the event object - a `KEVENT` structure. 

The first thing we need to do is locate the object from its handle table entry that we worked so hard to locate above. If we dump the contents of the handle table entry, we get something like this:

```
kd> dt nt!_HANDLE_TABLE_ENTRY ffffe58422064220
   +0x000 VolatileLowValue : 0n-7601665455979233279
   +0x000 LowValue         : 0n-7601665455979233279
   +0x000 InfoTable        : 0x9681758b`0b000001 _HANDLE_TABLE_ENTRY_INFO
   +0x008 HighValue        : 0n2031619
   +0x008 NextFreeHandleEntry : 0x00000000`001f0003 _HANDLE_TABLE_ENTRY
   +0x008 LeafHandleValue  : _EXHANDLE
   +0x000 RefCountField    : 0n-7601665455979233279
   +0x000 Unlocked         : 0y1
   +0x000 RefCnt           : 0y0000000000000000 (0)
   +0x000 Attributes       : 0y000
   +0x000 ObjectPointerBits : 0y10010110100000010111010110001011000010110000 (0x9681758b0b0)
   +0x008 GrantedAccessBits : 0y0000111110000000000000011 (0x1f0003)
   +0x008 NoRightsUpgrade  : 0y0
   +0x008 Spare1           : 0y000000 (0)
   +0x00c Spare2           : 0
```

The `ObjectPointerBits` field contains the address of the object header for the object to which this handle refers. This output reports that the address of our object is `0x9681758b0b0`, but that can't be right - that address is way too low to be the actual address of the object header somewhere in system space. Indeed, we need to perform a simple computation in order to derive the actual address from these bits. ReactOS defines the following macro to compute the address of the object header from a pointer to the handle table entry:

```
 #define ObpGetHandleObject(x)                           \
     ((POBJECT_HEADER)((ULONG_PTR)x->Object & ~OBJ_HANDLE_ATTRIBUTES))
```

The `OBJ_HANDLE_ATTRIBUTES` is defined as follows:

```
 #define OBJ_PROTECT_CLOSE                               0x01
 //#define OBJ_INHERIT                                   0x02
 #define OBJ_AUDIT_OBJECT_CLOSE                          0x04
 #define OBJ_HANDLE_ATTRIBUTES                           (OBJ_PROTECT_CLOSE |\
                                                          OBJ_INHERIT |      \
                                                          OBJ_AUDIT_OBJECT_CLOSE)
```

Thus, we can compute this macro ourselves using our value for `ObjectPointerBits` to determine the address of the object header:

```
kd> ? 0x4 | 0x2 | 0x1
Evaluate expression: 7 = 00000000`00000007
kd> ?? (ULONGLONG)(~0x0000000000000007)
ULONGLONG 0xffffffff`fffffff8
kd> ? 0x9681758b0b00 & 0xfffffffffffffff8
Evaluate expression: 165482766994176 = 00009681`758b0b00
kd> ? 00009681`758b0b00 | 0xffff000000000000
Evaluate expression: -115992209716480 = ffff9681`758b0b00
```

So we end up with a final object header address of `0xffff9681758b0b00`, which matches the output from `!handle`. Now that we've located the Object Manager information, we can get to the good stuff.

**Determining the Object Type**

Without further ado we can dump the contents of the object header for our event object:

```
1: kd> dt nt!_OBJECT_HEADER ffff9681758b0b00
   +0x000 PointerCount     : 0n2
   +0x008 HandleCount      : 0n1
   +0x008 NextToFree       : 0x00000000`00000001 Void
   +0x010 Lock             : _EX_PUSH_LOCK
   +0x018 TypeIndex        : 0x4f 'O'
   +0x019 TraceFlags       : 0 ''
   +0x019 DbgRefTrace      : 0y0
   +0x019 DbgTracePermanent : 0y0
   +0x01a InfoMask         : 0xa ''
   +0x01b Flags            : 0 ''
   +0x01b NewObject        : 0y0
   +0x01b KernelObject     : 0y0
   +0x01b KernelOnlyAccess : 0y0
   +0x01b ExclusiveObject  : 0y0
   +0x01b PermanentObject  : 0y0
   +0x01b DefaultSecurityQuota : 0y0
   +0x01b SingleHandleEntry : 0y0
   +0x01b DeletedInline    : 0y0
   +0x01c Reserved         : 0xffffe584
   +0x020 ObjectCreateInfo : 0xffff9681`72eb1d40 _OBJECT_CREATE_INFORMATION
   +0x020 QuotaBlockCharged : 0xffff9681`72eb1d40 Void
   +0x028 SecurityDescriptor : 0xffffe584`1fb6116e Void
   +0x030 Body             : _QUAD
```

The `OBJECT_HEADER` contains plenty of interesting information, but the first one we are going to focus on is the `TypeIndex` field, which will allow us to determine the type of the object to which this header is attached. The type index field reports a value of `0x4f`, but alas using this index to actually locate the corresponding type object is no simple matter - Windows adds a layer of obfuscation here as a security mechanism (more details regarding the rationale behind this design can be found [in this article](https://medium.com/@ashabdalhalim/a-light-on-windows-10s-object-header-typeindex-value-e8f907e7073a)).

The first thing we have to do is XOR the type index value with the second-least-significant byte of the address of the object header itself, which in our case is `0xffff9681758b0b00`. The second-least-significant byte is `0x0b`, so this is the value we need to XOR against our type index. 

Unfortunately that is not the whole story - we also need to XOR our type index value from the object header with the value of `nt!ObHeaderCookie`:

```
kd> db nt!ObHeaderCookie L1
fffff807`7f774680  54  
```

So the byte value of `nt!ObHeaderCookie` is `0x54`. Thus, our final expression becomes:

```
kd> ? 0x4f ^ 0x0b ^ 0x54
Evaluate expression: 16 = 00000000`00000010
```

So the actual type index we are looking for is 16, or `0x10`. We can now use this value as a valid index into the object type index table, located by the `ntObTypeIndexTable` symbol:

```
kd> dt nt!_OBJECT_TYPE poi(nt!ObTypeIndexTable + ( 0x10 * @$ptrsize ))
   +0x000 TypeList         : _LIST_ENTRY [ 0xffffbe04`114b8c40 - 0xffffbe04`114b8c40 ]
   +0x010 Name             : _UNICODE_STRING "Event"
   +0x020 DefaultObject    : (null) 
   +0x028 Index            : 0x10 ''
   +0x02c TotalNumberOfObjects : 0x2072
   +0x030 TotalNumberOfHandles : 0x226e
   +0x034 HighWaterNumberOfObjects : 0x26d0
   +0x038 HighWaterNumberOfHandles : 0x292f
   +0x040 TypeInfo         : _OBJECT_TYPE_INITIALIZER
   +0x0b8 TypeLock         : _EX_PUSH_LOCK
   +0x0c0 Key              : 0x6e657645
   +0x0c8 CallbackList     : _LIST_ENTRY [ 0xffffbe04`114b8d08 - 0xffffbe04`114b8d08 ]
```

Quite a bit of work just to confirm that we are indeed dealing with an event object.

**Parsing Object Optional Headers**

Above, we were reminded that the overall memory layout for an object and its metadata has the following structure:

```
------------------------
      Pool Header
------------------------
   Optional Header(s)
------------------------
      Object Header
------------------------
       Object Body
------------------------
```

So the object header may be preceded by anywhere from zero to five optional headers that provide additional object information. In the event they are present, these object headers are arranged as follows:

```
-------------------------------
  OBJECT_HEADER_PROCESS_INFO
-------------------------------
    OBJECT_HEADER_QUOTA_INFO
-------------------------------
   OBJECT_HEADER_HANDLE_INFO
-------------------------------
    OBJECT_HEADER_NAME_INFO
-------------------------------
   OBJECT_HEADER_CREATOR_INFO
-------------------------------
         OBJECT_HEADER
-------------------------------
```

The optional headers are always maintained in this order, but again, each header may or may not be present at all. How do we determine which optional headers are present? The `InfoMask` field of the `OBJECT_HEADER` itself provides this information:

```
1: kd> dt nt!_OBJECT_HEADER ffff9681758b0b00
   ...
   +0x01a InfoMask         : 0xa ''
```

Each optional header is assigned a single bit in this 5-bit wide field:

|            Header            | Bit Index | Value |
|:----------------------------:|:---------:|:-----:|
| `OBJECT_HEADER_CREATOR_INFO` |     0     |   0x1 |
| `OBJECT_HEADER_NAME_INFO`    |     1     |   0x2 |
| `OBJECT_HEADER_HANDLE_INFO`  |     2     |   0x4 |
| `OBJECT_HEADER_QUOTA_INFO`   |     3     |   0x8 |
| `OBJECT_HEADER_PROCESS_INFO` |     4     |  0x10 |

Thus, the value `0xa`, which translates to the binary `0b10010` indicates that the `OBJECT_HEADER_NAME_INFO` and `OBJECT_HEADER_PROCESS_INFO` optional headers are present.

To compute the offset to a particular header, Windows maintains a globally accessible table that allows us to compute the offset value given the value of the `InfoMask` and the desired header bit. The table is accessible via the `nt!ObpInfoMaskToOffset` symbol:

```
1: kd> ? nt!ObpInfoMaskToOffset
Evaluate expression: -8763890958528 = fffff807`7f647f40
```

The algorithm for computing the optional header offset using this table is represented in pseudocode as follows: 

```
Offset = ObpInfoMaskToOffset[OBJECT_HEADER->InfoMask & (DesiredHeaderBit | (DesiredHeaderBit-1))]
```

We can implement this algorithm in the debugger to compute the offset from the base of the object header to the base of the `OBJECT_HEADER_NAME_INFO` optional header:

```
kd> ?? ((unsigned char *)@@masm(nt!ObpInfoMaskToOffset))[0xa & (0x02 | (0x02-1))]
unsigned char 0x20 ' '
```

Similarly, we can compute the offset from the base of the object header to the base of the `OBJECT_HEADER_PROCESS_INFO` optional header:

```
kd> ?? ((unsigned char *)@@masm(nt!ObpInfoMaskToOffset))[0xa & (0x10 | (0x10-1))]
unsigned char 0x40 '@'
```

Now we can examine these structures ourselves. First the `OBJECT_HEADER_NAME_INFO` optional header. (Fun fact: the method for computing the location of this header relative to the object header base presented in _Windows Internals, 6th Edition Part 1_ is incorrect, as we demonstrate here!)

```
kd> dt nt!_OBJECT_HEADER_NAME_INFO 0xffff9681758b0b00-0x20
   +0x000 Directory        : 0xffffe584`1e4bc380 _OBJECT_DIRECTORY
   +0x008 Name             : _UNICODE_STRING "Event1234"
   +0x018 ReferenceCount   : 0n0
   +0x01c Reserved         : 0
```

So our event object gets a `OBJECT_HEADER_NAME_INFO` optional header because we assigned it a name at the time of creation.

Similarly, we can dump the `OBJECT_HEADER_PROCESS_INFO` optional header:

```
kd> dt nt!_OBJECT_HEADER_PROCESS_INFO 0xffff9681758b0b00-0x40
   +0x000 ExclusiveProcess : 0x00000070`00000000 _EPROCESS
   +0x008 Reserved         : 0
```

In the event that this was an _exclusive object_, this optional header would contain a pointer to the `EPROCESS` for the owning process. However, our event object is not exclusive object, so this optional header is relatively uninteresting.

**Examining the Underlying Object**

Thus far all we've done is look at our event object's metadata; now it is finally time to turn our attention to the event object itself. We already know the address of the base of the `OBJECT_HEADER`, so we could easily add the size of the object header to this address to get the base address for the object itself. Alternatively, the output of `!handle` performs this calculation for us:

```
1: kd> !handle 0 3 ffff96817396c4c0 Event

Searching for handles of type Event

PROCESS ffff96817396c4c0
    SessionId: 1  Cid: 1514    Peb: c8b6877000  ParentCid: 170c
    DirBase: 287a4002  ObjectTable: ffffe5842266a600  HandleCount:  35.
    Image: handle_table.exe

Handle table at ffffe5842266a600 with 35 entries in use

   ...

0088: Object: ffff9681758b0b30  GrantedAccess: 001f0003 Entry: ffffe58422064220
Object: ffff9681758b0b30  Type: (ffff96816e6a7c40) Event
    ObjectHeader: ffff9681758b0b00 (new version)
        HandleCount: 1  PointerCount: 2
        Directory Object: ffffe5841e4bc380  Name: Event1234
```

We can use the address reported in the `Object` field to dump the body of the event:

```
1: kd> dt nt!_KEVENT ffff9681758b0b30
   +0x000 Header           : _DISPATCHER_HEADER
```

A major anti-climax... The only member of the event object is a `DISPATCHER_HEADER` structure (or at least, this is the only member provided by the public symbols that we have). The `DISPATCHER_HEADER` is an extremely important structure - it is at the heart of how Windows implements kernel-assisted synchronization, and is the underlying structure that provides synchronization functionality for all of the synchronization primitives that we know and love (events, mutexes, semaphores, critical sections, etc.) However, this a huge topic on its own, so examining the internals of how Windows implements sychronization via dispatcher objects will have to wait for a future exercise.

This concludes our foray into the process handle table and the internals of the Object Manager. Hopefully this exercise has helped you develop an appreciation for just how much is going on behind the scenes to implement the beautiful resource management abstraction presented to us as user-mode programmers via object `HANDLE`s.

