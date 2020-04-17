## The Portable Executable File Format

This module covers the binary format utilized by native Windows programs - the Portable Executable file format (PE32 and PE32+). 

### Key Concepts

- MS-DOS Header and Stub
- COFF File Header
- Optional Header
- PE Data Directories
- PE Section Headers and Sections
- PE Export Directory
- PE Import Directory
- PE Image Relocations

### Reading Material

- [An In-Depth Look into the Win32 Portable Executable File Format (Part 1)](http://bytepointer.com/resources/pietrek_in_depth_look_into_pe_format_pt1.htm)
- [An In-Depth Look into the Win32 Portable Executable File Format (Part 2)](http://bytepointer.com/resources/pietrek_in_depth_look_into_pe_format_pt2.htm)

### Optional Reading Material

- [MSDN: PE Format](https://docs.microsoft.com/en-us/windows/win32/debug/pe-format)
    - The Microsoft-provided documentation of the PE file format. Comprehensive and informative, if a bit dry.
- [External Content: The Life Of Binaries](http://opensecuritytraining.info/LifeOfBinaries.html)
    - A full training course freely available on OpenSecurityTraining that covers both the Portable Executable file format as well as the loading and execution process. 

### Checks on Learning

- The DOS Header, File Header, and Optional Header all appear in Windows image files (executables and dynamic libraries). Which, if any, are included in Windows object (`.obj`) files? Windows static library (`.lib`) files?
- Which field in which PE header is the true determinant of whether the image is 32-bit (PE32) or 64-bit (PE32+)?
- In the context of Portable Executable file parsing, what is the difference between Absolute Virtual Addresses (AVAs) and Relative Virtual Addresses (RVAs)?
- If a Portable Executable file is loaded at base address `0x80000000` and the AVA of the entry point to some function defined in the file's `.text` section is `0xC123000F`, what is the RVA of the function's entry point?
- If a Portable Executable file is loaded at base address `0x80000000` and the RVA of the entry point to some function defined in the file's `.text` section is `0x1000`, what is the AVA of the function's entry point?
- Suppose some application source defines a global variable `int g_data = 1337`. In which Portable Executable section would you expect to find the data `1337`?
- Suppose some application source defines a global variable `const int g_data = 1337`. In which Portable Executable section would you expect to find the data `1337`?
- Suppose some application source defines a global variable `char* g_str = "hello world"`. In which Portable Executable section would you expect to find the data `"hello world"`?
- Suppose some application source defines a local (automatic, stack allocated) variable `char* l_str = "hello world"`. In which Portable Executable section would you expect to find the data `"hello world"`?
- Suppose some executable imports and utilizes seven (7) functions from three (3) external libraries (static or dynamic). How many `IMAGE_IMPORT_DESCRIPTOR` structures would you expect to find in the Import Directory of the image?
- Under what circumstances may the `NumberOfFunctions` field of the `IMAGE_EXPORT_DIRECTORY` structure differ from the `NumberOfNames` field? 
- Suppose the Relocation Directory for some executable contains an `IMAGE_BASE_RELOCATION` structure with `VirtualAddress` field equal to `0x3000` and a relocation target equal to `0x32FB` (`SizeOfBlock` is immaterial here). Further, suppose that the `ImageBase` field of the executable's Optional Header is equal to `0x140000000` and that the image is loaded at a base address of `0x14060000`. How would the loader complete relocation for this particular relocation target?
- In which system header file may you find type and structure definitions related to Windows Portable Executable files?