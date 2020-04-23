## Reading Files
Reading Files using a file handle

### Background
Knowing how to use file handles and how they work is crucial to understanding the underlying concepts of Windows programming.

### Project Structure

This exercise will reinforce the concept of consecutive reads on the same file handle. It will also be used to examine the underlying structure of a file object.

### Procedure

Objectives
- Write a program that opens sample.txt and reads in three bytes at a time into a buffer. Once you have finished reading the file, print out the buffer. The output will tell you if you were successful or not.

- After writing the initial program, insert a debugbreak() after your first read. Compile and run the program in a kernel mode windbg. Run the program until you hit the debug break, look at RCX to get the handle.


`!handle (value in rcx)`

Your output should look similiar to this one

```
006c: Object: ffffe001283ddf20  GrantedAccess: 00100081 (Protected) (Inherit) (Audit) Entry: ffffc000d2d5b1b0
Object: ffffe001283ddf20  Type: (ffffe001249b49a0) File
    ObjectHeader: ffffe001283ddef0 (new version)
        HandleCount: 1  PointerCount: 32768
        Directory Object: 00000000  Name: \sample.txt {HarddiskVolume3}
```


 
`dt nt!_OBJECT_HEADER ffffe001283ddef0`
`dt nt!_FILE_OBJECT (ffffe001283ddef0 + 0x30)`

Look at the CurrentByteOffset field, continue to hit Go(F5) and watch as the number increments