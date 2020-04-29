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