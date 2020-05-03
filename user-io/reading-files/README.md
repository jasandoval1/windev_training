## Exercise: Reading Files

This exercise will introduce you to reading filesystem files using a Windows handle.

### Background

Knowing how to use file handles and how they work is crucial to understanding the underlying concepts of Windows programming.

### Project Structure

This exercise will reinforce the concept of consecutive reads on the same file handle. It will also be used to examine the underlying structure of a file object.

### Procedure

Objectives:
- Write a program that opens the file `sample.txt` and reads three bytes at a time into a buffer. Once you have finished reading the file, print out the buffer's contents. The output will tell you if you were successful or not.
- After writing the initial program, insert a `debugbreak()` after your first read operation. Compile and run the program in a VM to which you have attached a kernel debugger. Run the program until the debug breakpoint is hit. 

Examine the contents of the RCX register to determine the value of the handle:

```
!handle (value in rcx)
```

Your output should appear similar to the following:

```
1: kd> !handle 6c

PROCESS ffffe00128780080
    SessionId: 1  Cid: 0a80    Peb: 7ff617654000  ParentCid: 0d5c
    DirBase: 080e5000  ObjectTable: ffffc000d43244c0  HandleCount: <Data Not Accessible>
    Image: test.exe

Handle Error reading handle count.

006c: Object: ffffe001283ddf20  GrantedAccess: 00100081 (Protected) (Inherit) (Audit) Entry: ffffc000d2d5b1b0
Object: ffffe001283ddf20  Type: (ffffe001249b49a0) File
    ObjectHeader: ffffe001283ddef0 (new version)
        HandleCount: 1  PointerCount: 32768
        Directory Object: 00000000  Name: \sample.txt {HarddiskVolume3}


```

Use the output from the `!handle` command to locate and subsequently dump the contents of the `OBJECT_HEADER` for the file object:

```
1: kd> dt nt!_OBJECT_HEADER ffffe001283ddef0
   +0x000 PointerCount     : 0n32768
   +0x008 HandleCount      : 0n1
   +0x008 NextToFree       : 0x00000000`00000001 Void
   +0x010 Lock             : _EX_PUSH_LOCK
   +0x018 TypeIndex        : 0x9e ''
   +0x019 TraceFlags       : 0 ''
   +0x019 DbgRefTrace      : 0y0
   +0x019 DbgTracePermanent : 0y0
   +0x01a InfoMask         : 0x4d 'M'
   +0x01b Flags            : 0x40 '@'
   +0x01b NewObject        : 0y0
   +0x01b KernelObject     : 0y0
   +0x01b KernelOnlyAccess : 0y0
   +0x01b ExclusiveObject  : 0y0
   +0x01b PermanentObject  : 0y0
   +0x01b DefaultSecurityQuota : 0y0
   +0x01b SingleHandleEntry : 0y1
   +0x01b DeletedInline    : 0y0
   +0x01c Spare            : 0
   +0x020 ObjectCreateInfo : 0xffffe001`2752f0c0 _OBJECT_CREATE_INFORMATION
   +0x020 QuotaBlockCharged : 0xffffe001`2752f0c0 Void
   +0x028 SecurityDescriptor : (null) 
   +0x030 Body             : _QUAD
```

Now parse the body of the file object (`FILE_OBJECT`) itself. The body of the file object immediately follows the object header in memory, so all we need to do is add the size of the `OBJECT_HEADER` to the address of the header's base to locate the body of the file object:

```
1: kd>?? sizeof(nt!_OBJECT_HEADER)
unsigned int64 0x30
1: kd> dt nt!_FILE_OBJECT (ffffe001283ddef0 + 0x30)
   +0x000 Type             : 0n5
   +0x002 Size             : 0n216
   +0x008 DeviceObject     : 0xffffe001`26bed060 _DEVICE_OBJECT
   +0x010 Vpb              : 0xffffe001`26bedfa0 _VPB
   +0x018 FsContext        : 0xffffc000`d5b18b70 Void
   +0x020 FsContext2       : 0xffffc000`d39e9010 Void
   +0x028 SectionObjectPointer : 0xffffe001`27867288 _SECTION_OBJECT_POINTERS
   +0x030 PrivateCacheMap  : 0xffffe001`248ca678 Void
   +0x038 FinalStatus      : 0n0
   +0x040 RelatedFileObject : (null) 
   +0x048 LockOperation    : 0 ''
   +0x049 DeletePending    : 0 ''
   +0x04a ReadAccess       : 0x1 ''
   +0x04b WriteAccess      : 0 ''
   +0x04c DeleteAccess     : 0 ''
   +0x04d SharedRead       : 0 ''
   +0x04e SharedWrite      : 0 ''
   +0x04f SharedDelete     : 0 ''
   +0x050 Flags            : 0xc0042
   +0x058 FileName         : _UNICODE_STRING "\sample.txt"
   +0x068 CurrentByteOffset : _LARGE_INTEGER 0x3
   +0x070 Waiters          : 0
   +0x074 Busy             : 0
   +0x078 LastLock         : (null) 
   +0x080 Lock             : _KEVENT
   +0x098 Event            : _KEVENT
   +0x0b0 CompletionContext : (null) 
   +0x0b8 IrpListLock      : 0
   +0x0c0 IrpList          : _LIST_ENTRY [ 0xffffe001`283ddfe0 - 0xffffe001`283ddfe0 ]
   +0x0d0 FileObjectExtension : (null) 
```

Examine the `CurrentByteOffset` field. Continue to hit `Go` (F5) and watch as the number increments with each successive read operation.