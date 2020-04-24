## EXERCISE NAME

Examining the SSDT

### Background

Nearly all functions require a transition to kernel mode to access underlying kernel objects. We exame the SSDT to determine how it all works under the hood.

### Project Structure

Examine the SSDT using IDA and WinDbg

### Procedure

This exercise will requre IDA and a kernel mode debugger (WinDbg)

- Open up ntdll.dll in IDA and look at the symbol ZwCreateFile

```
public ZwCreateFile
ZwCreateFile proc near
mov     r10, rcx        ; NtCreateFile
mov     eax, 55h
test    byte ptr ds:7FFE0308h, 1
jnz     short loc_18009CB15
```

Your entry will look similiar to the above but the index in the SSDT may be different. For my version of Windows it was 0x55.

In your kernel debuger type the following command
`x nt!KeServiceDescriptorTable`

```
1: kd> x nt!KeServiceDescriptorTable
fffff800`fc844740 nt!KeServiceDescriptorTable = <no type information>
```


This is the structure that the SSDT uses
```
typedef struct SYSTEM_SERVICE_TABLE {
    PULONG ServiceTable;
    PULONG_PTR CounterTable;
    ULONG_PTR ServiceLimit;
    PBYTE ArgumentTable;
} SYSTEM_SERVICE_TABLE;
```

Servicetable is the base address of the System Service Descriptor Table (SSDT) and the ServiceLimit is the number of services in the table.

List the SSDT with the following command
`dq /c 1 fffff800fc844740 L4`

```
1: kd> dq /c 1 fffff800fc844740 L4
fffff800`fc844740  fffff800`fc786640
fffff800`fc844748  00000000`00000000
fffff800`fc844750  00000000`000001b9
fffff800`fc844758  fffff800`fc78740c
```

Now that we have the base address of the service table, lets see if we can find NtCreatefile. The SSDT is an array of DWORDS in both 32/64. In 32bit the SSDT entries are the absolute address of the function. In 64 bit, it is an offset from the base address of the table. We need to account for the 0 index so we need to add one to our SSDT index we found earlier.
`dd /c 1 fffff800fc786640 L 0x56`

```
fffff800`fc786794  017ac307
```

Windows calculates the address of the function by taking the number of arguments to CreateFile (7) and adding it to the offset. So we need to >> 4 before calculating the offset.

In windbg
`? 017ac307 >> 4`

```
1: kd> ? 017ac307 >> 4
Evaluate expression: 1551408 = 000000000017ac30
```

Now we have everything we need, we have our base SSDT address and our offset to our function. The command 'ln' is used to look for symbols near this address.

`ln (fffff800fc786640 + 000000000017ac30)`

```
1: kd> ln (fffff800fc786640 + 000000000017ac30)

(fffff800`fc901270)   nt!NtCreateFile   |  (fffff800`fc9012f4)   nt!NtOpenKey
Exact matches:
    nt!NtCreateFile (<no parameter info>)

```

We found NtCreateFile that is exported by NtosKrnl