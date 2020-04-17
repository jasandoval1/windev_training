## Static and Dynamic Libraries

This module builds on the previous module regarding the Windows binary file format by introducing software libraries and how they relate to standard executables.

### Key Concepts

- Windows static libraries (`.lib`)
- Windows dynamic libraries (`.dll`)
- Exporing functions from static and dynamic libraries
- Consuming dynamic libraries via implicit linking
- Consuming dynamic libraries via explicit linking
- Development tradeoffs between use of static and dynamic libraries
- Deployment tradeoffs between use of static and dynamic libraries 

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 167-177
    - This section introduces the distinction between static and dynamic libraries, the various motivations for using dynamic libaries, and basic dynamic link library (DLL) usage.
- _Windows Via C/C++, Fifth Edition_: Pages 537-552
    - This section presents a worked example of building a DLL and utilizing its functionality within the context of an executable program. 
- _Windows Via C/C++, Fifth Edition_: Pages 553-596
    - This section provides important information regarding the operation and resolution of DLL dependencies. 
- _Windows Via C/C++, Fifth Edition_: Pages 605-658
    - This section describes slightly more advanced techniques involving DLLs, including user-mode API hooking and DLL injection. 

### Checks on Learning

- Describe two (2) strategies for exporting data or a function from a dynamic library.
- If your application makes use of some function exported by a dynamic library via _implicit linking_, who is responsible for resolving the external function? When does this resolution take place in the lifetime of the program?
- If your application makes use of some function exported by a dynamic library via _explicit linking_, who is responsible for resolving the external function? When does this resolution take place in the lifetime of the program?
- Suppose you want to utilize some function exported by a dynamic library via explicit linking. Assuming the library is not yet loaded into the process context, which Win32 function(s) would you call to resolve the desired function?
- Suppose a dynamic library defines and exports a global variable `int g_data = 1337`. Further, suppose that two processes, _Process A_ and _Process B_ startup and load the dynamic library. If _Process A_ sets the value of `g_data` to `1054`, what is the value of `g_data` in the context of _Process B_?
- Describe one benefit of utilizing a dynamic library instead of a static library in the context of application development.
- Describe one benefit of utilizing a static library instead of a dynamic library in the context of application development.
- Describe one benefit of utilizing a dynamic library instead of a static library in the context of application deployment.
- Describe one benefit of utilizing a static library instead of a dynamic library in the context of application deployment.