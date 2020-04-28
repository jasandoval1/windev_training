## Exercise: Exploring the Process Handle Table

### Procedure

Locating a specific object.

```
kd> !process 0 1 handle_table.exe
PROCESS ffffbe0417a0d4c0
    SessionId: 1  Cid: 0ccc    Peb: 5a822cf000  ParentCid: 1084
    DirBase: 07a96002  ObjectTable: ffff9c073324e4c0  HandleCount:  35.
    Image: handle_table.exe
    VadRoot ffffbe0417a298b0 Vads 20 Clone 0 Private 94. Modified 0. Locked 2.
    DeviceMap ffff9c07302cf770
    ...
```

```
kd> !handle 0 3 ffffbe0417a0d4c0 Event
    ...
0088: Object: ffffbe0417a2cc60  GrantedAccess: 001f0003 (Protected) (Inherit) Entry: ffff9c0731cfe220
Object: ffffbe0417a2cc60  Type: (ffffbe04114b8c40) Event
    ObjectHeader: ffffbe0417a2cc30 (new version)
        HandleCount: 1  PointerCount: 2
        Directory Object: ffff9c072f0aca20  Name: Event1234
```

Determining the type from the object header.

Further explanation of this process is available [in this article](https://medium.com/@ashabdalhalim/a-light-on-windows-10s-object-header-typeindex-value-e8f907e7073a).

```
kd> dt nt!_OBJECT_HEADER ffffbe0417a2cc30
   +0x000 PointerCount     : 0n2
   +0x008 HandleCount      : 0n1
   +0x008 NextToFree       : 0x00000000`00000001 Void
   +0x010 Lock             : _EX_PUSH_LOCK
   +0x018 TypeIndex        : 0x6f 'o'
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
   +0x01c Reserved         : 0xffff9c07
   +0x020 ObjectCreateInfo : 0xffffbe04`162b5040 _OBJECT_CREATE_INFORMATION
   +0x020 QuotaBlockCharged : 0xffffbe04`162b5040 Void
   +0x028 SecurityDescriptor : 0xffff9c07`30dfb9ae Void
   +0x030 Body             : _QUAD
```

```
    ...
   +0x018 TypeIndex        : 0x6f 'o'
   ...
```

Must XOR this type index value with the second-least-significant byte of the address of the object header:

```
kd> dt nt!_OBJECT_HEADER ffffbe0417a2cc30
```

So in the case of this particular object header, the second-least-significant byte is `0xcc`. But that's not the whole story - we also need to XOR the type index value from the object header with the value of `nt!ObHeaderCookie`:

```
0: kd> db nt!ObHeaderCookie L1
fffff800`4be26680  b3
```

So the byte value of `nt!ObHeaderCookie` is `0xb3`. Thus, our final expression becomes:

```
kd> ? cc ^ 6f ^ b3
Evaluate expression: 16 = 00000000`00000010
```

So the actual type index we are looking for is 16, or `0x10`. We can now use this value as a valid index into the object type index table, located by the `ntObTypeIndexTable` symbol:

```
kd> dt nt!_OBJECT_TYPE poi(nt!ObTypeIndexTable + ( 10 * @$ptrsize ))
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

Parsing object optional headers. 

```
POOL_HEADER
OBJECT_HEADER_PROCESS_INFO
OBJECT_HEADER_QUOTA_INFO
OBJECT_HEADER_HANDLE_INFO
OBJECT_HEADER_NAME_INFO
OBJECT_HEADER_CREATOR_INFO
OBJECT_HEADER
OBJECT
```

```
kd> dt nt!_OBJECT_HEADER ffff8c098a432cc0
    ...
   +0x01a InfoMask         : 0xa ''
```

Each optional header is assigned a bit in this 5-bit wide field. Thus, the value `0xa`, which translates to the binary `0b10010` indicates that the `OBJECT_HEADER_NAME_INFO` and `OBJECT_HEADER_PROCESS_INFO` optional headers are present.

```
Offset = ObpInfoMaskToOffset[OBJECT_HEADER->InfoMask & (DesiredHeaderBit | (DesiredHeaderBit-1))]
```

Offset to from the base of the object header to the base of the `OBJECT_HEADER_NAME_INFO`:

```
kd> ?? ((unsigned char *)@@masm(nt!ObpInfoMaskToOffset))[0xa & (0x02 | (0x02-1))]
unsigned char 0x20 ' '
```

Offset to from the base of the object header to the base of the `OBJECT_HEADER_PROCESS_INFO`:

```
kd> ?? ((unsigned char *)@@masm(nt!ObpInfoMaskToOffset))[0xa & (0x10 | (0x10-1))]
unsigned char 0x40 '@'
```

Now we can examine these structures ourselves. First the `OBJECT_HEADER_NAME_INFO` header. Note that the method for computing the location of this header relative to the object header base presented in _Windows Internals, 6th Edition Part 1_ is incorrect.

```
kd> dt nt!_OBJECT_HEADER_NAME_INFO ffff8c098a432cc0-0x20
   +0x000 Directory        : 0xffffd60d`7da97de0 _OBJECT_DIRECTORY
   +0x008 Name             : _UNICODE_STRING "Event1234"
   +0x018 ReferenceCount   : 0n0
   +0x01c Reserved         : 0x300031
```

And the `OBJECT_HEADER_PROCESS_INFO`.

```
kd> dt nt!_OBJECT_HEADER_PROCESS_INFO ffff8c098a432cc0-0x40
   +0x000 ExclusiveProcess : 0x00000070`00000000 _EPROCESS
   +0x008 Reserved         : 0x00700070`00000000
```

Looking at the pool header.

```
kd> ?? sizeof(nt!_OBJECT_HEADER_NAME_INFO)
unsigned int64 0x20
kd> ?? sizeof(nt!_OBJECT_HEADER_PROCESS_INFO)
unsigned int64 0x10
kd> ?? sizeof(nt!_POOL_HEADER)
unsigned int64 0x10
```

```
kd> dt nt!_POOL_HEADER ffff8c098a432cc0-0x20-0x10-0x10
   +0x000 PreviousSize     : 0y00000000 (0)
   +0x000 PoolIndex        : 0y00000000 (0)
   +0x002 BlockSize        : 0y00000000 (0)
   +0x002 PoolType         : 0y00000000 (0)
   +0x000 Ulong1           : 0
   +0x004 PoolTag          : 0x70
   +0x008 ProcessBilled    : 0x00700070`00000000 _EPROCESS
   +0x008 AllocatorBackTraceIndex : 0
   +0x00a PoolTagHash      : 0
```

Looking at the underlying object.

```
kd> dt nt!_KEVENT ffff8c098a432cf0
   +0x000 Header           : _DISPATCHER_HEADER
```

Looking at the internals of how Windows implements sychronization through dispatcher objects will be left for a future exercise.