## Loading and Executing Windows Binaries

This module builds on the last two by exploring the details behind the loading and execution of native Windows binaries (i.e. not managed or Windows runtime applications) - how we get from a binary file on disk to `main()` or `DllMain()`.

### Reading Material

- _Windows Internals, Seventh Edition, Part 1_: 155-176
    - This section covers, in excruciating detail, the procedure followed by the Windows Image Loader to load a binary file from disk and prepare it for execution.

### Optional Reading Material

- [External Content: The Life Of Binaries](http://opensecuritytraining.info/LifeOfBinaries.html)
    - A full training course freely available on OpenSecurityTraining that covers both the Portable Executable file format as well as the loading and execution process. 