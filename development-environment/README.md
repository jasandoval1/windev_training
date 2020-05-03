## Development Environment Setup and Windows Development Tools

This module provides an introduction to the most important tools that Windows provides to support developers.

### Key Concepts

- Visual Studio solution / project distinction and organization
- Visual Studio configuration manager purpose and usage
- Visual Studio property pages purpose usage
- Visual Studio custom build events purpose and usage
- Visual Studio keyboard shortcut definition and usage
- Microsoft Visual C/C++ Runtime Library description and usage 
- Basic Visual Studio debugger usage 
- Basic WinDbg debugger usage

### Reading Material

- _Professional Visual Studio 2017_: Chapter 6 - Solutions, Projects, and Items
    - This chapter introduces essential Visual Studio terminology and the basics of setting up a new solution.
- _Professional Visual Studio 2017_: Chapter 30 - Using the Debugging Windows
    - This chapter offers an overview of and orientation to the debugging features offered by Visual Studio.
- _Professional Visual Studio 2017_: Chapter 31 - Debugging with Breakpoints
    - This chapter picks up where the previous chapter left off and goes deeper into how one utilizes the Visual Studio debugging tools to rapidly debug an application under active development.

### Exercises

- [Creating Complex Solutions in Visual Studio](./vs-solutions)
- [User Mode Debugging Essentials (WinDbg)](./windbg-user-mode)
- [User Mode Debugging Essentials (Visual Studio)](./vs-debugging)
- [Unit Testing Essentials (Visual Studio and Microsoft Unit Testing Framework)](./vs-unit-test-ms)
- [Unit Testing Essentials (Visual Studio and Google Test)](./vs-unit-test-google)
- [Unit Testing Essentials (CMake and Catch2)](./catch2-unit-test)
- [Kernel Debugging Setup](./kernel-debugging)

### Checks on Learning

- What is the purpose of the distinction between Visual Studio Solutions and Visual Studio Projects?
- Visual Studio is not magic - under the hood, it simply invokes the MSVC compiler (`cl.exe`) and linker (`link.exe`) to build native projects. How do you view the complete command line that Visual Studio is using to build your application? 
- Within Visual Studio, where is one able to modify the following build configuration options:
    - `#include` directories
    - Linker input directories
    - Linker input files
- What is the purpose of precompiled headers? How do you set up a project to make use of precompiled headers?
- What are the different variants of the Microsoft Visual C/C++ Runtime Library against which you can link your applications? When are each of these different variants appropriate?
- The Windows SDK and Windows Store provide a number of symbolic debuggers - WinDbg, WinDbg Preview, `cdb.exe`, etc. How are these tools similar? How are they different
- What is the difference between Debug/Release builds? 