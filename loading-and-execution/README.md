## Loading and Executing Windows Binaries

This module builds on the last two by exploring the details behind the loading and execution of native Windows binaries (i.e. not managed or Windows runtime applications) - how we get from a binary file on disk to `main()` or `DllMain()`.

### Key Concepts

- The Windows Image Loader
- Image relocation
- Import resolution
- DLL name resolution and search order

### Reading Material

- _Windows Internals, Seventh Edition, Part 1_: 155-176
    - This section covers, in excruciating detail, the procedure followed by the Windows Image Loader to load a binary file from disk and prepare it for execution.

### Optional Reading Material

- [External Content: The Life Of Binaries](http://opensecuritytraining.info/LifeOfBinaries.html)
    - A full training course freely available on OpenSecurityTraining that covers both the Portable Executable file format as well as the loading and execution process. 

### Checks on Learning

- In which module (dynamic library or executable image) is the first code to execute in the context of a newly-created Windows process defined?
- Under what circumstances must the executable image for a new Windows process be relocated?
- How might one specify that a dynamic library should only be loaded at a specific base address? What happens in the event that such a library cannot be loaded at this specified base address?
- During which point(s) in the lifecycle of a Windows process does the Windows Image Loader execute?
- Dynamic library dependencies are often recursive; for instance, your application may dynamically link _Module X_ and Kernel32 and _Module X_ may in turn dynamically link Kernel32. In such instances, how does the Windows Image Loader prevent loading the same module into a process context multiple times?
- What are the two methods by which functions exported by a dynamic library may be imported by an executable or another dynamic library?
- What is the difference between standard dynamic library imports and _delay-load_ imports? When are delay-load imports resolved?
- What are _bound imports_? Why are bound imports relatively unpopular in modern applications?
- How would you specify an alternate search algorithm for resolving dynamic library dependencies when using explicit (_runtime_) linking?
- What are _Known DLLs_? How is a dependency on a Known DLL resolved?
- How would you determine the dynamic libraries that qualify as Known DLLs on your system?
- At what point during process startup is the entry point for loaded dynamic libraries (e.g. `DllMain()`) invoked?
