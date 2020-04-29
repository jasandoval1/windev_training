## The Component Object Model and The Windows Runtime

This module provides a (brief) introduction to the Component Object Model (COM) and the Windows runtime API. While COM may appear to be merely an archaic, overly-verbose programming model which is now rarely used (which is true to a certain extent), Microsoft has chosen to implement the Windows Runtime on top of the fundamental concepts upon which COM is built. The Windows Runtime is an important technology in that it is the mechanism by which Microsoft will expose new operating system functionality to user-mode applications going forward.

### Learning Objectives

- Underlying motivation for COM and the Windows Runtime
- The COM programming model
- The Windows Runtime vs the Win32 API
- Windows Runtime implementation

### Reading Material

- [COM as a Better C++](./resources/essential_com_ch1.pdf)
    - The first chapter from Don Box's _Essential COM, First Edition_. This chapter demonstrates the motivation for COM and subsequently engineers its fundamentals from first principles.

### Optional Reading Material

- [MSDN: Introduction to C++/WinRT](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt)
    - This article introduces _C++/WinRT_ - the standard C++ language projection for the Windows runtime. For native application developers, this is the most important aspect of the Windows Runtime to master because it is the only part of WinRT to which they will be regularly exposed.
- _CLR via C#, Fourth Edition_: Pages 643-665
    - This section provides solutions to common problems and patterns for effective development when interoperating between managed code and the Windows Runtime.

### Checks on Learning

- How does C++ _name mangling_ limit the portability of C++ libraries distributed as dynamic libraries?
- How is it possible for modifications limited to private data members of C++ classes to render them incompatible with client applications that are not recompiled to account for these changes?
- Why are C++ virtual functional calls an appropriate abstraction for implementing portable binary interfaces?
- Why is it a requirement that COM interfaces are limited to deriving from a single parent interface?
- Why is it necessary to prevent client code from invoking `delete` on pointers returned by COM factory functions directly?
- Once a COM interface has been published, is it ever appropriate to modify it?
- Is it appropriate to implement a COM class that derives from more than one COM interface? 
- What is the name of the function exposed by COM's `IUnknown` interface that allows for dynamic (runtime) interrogation of the functionality supported by COM object's?
- What is the name of the function exposed by COM's `IUnknown` interface that increments the reference count for a COM object?
- What is the name of the function exposed by COM's `IUnknown` interface that decrements the reference count for a COM object? 