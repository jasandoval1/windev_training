## .NET and Managed Applications

This module provides a (brief) introduction to .NET and the execution model utilized by managed applications - applications that target the .NET Framework or .NET Core (the difference between these two will be covered shortly!). While .NET is but one among many technologies built on top of the Windows operating system, it is one that holds a privileged place in the hearts and minds of Microsoft's engineers and Windows application developers alike; a passing familiarity with the platform is a necessary precondition for understanding many of the design decisions introduced in recent versions of Windows.

Note that the .NET "brand" has grown to encompass a truly impressive number of technologies; therefore, this module surely does not attempt to introduce them all. Instead, it focuses on the core concepts that are at the heart of .NET in the belief that a firm grounding in these fundamentals prepares one for further research into any of the remaining more-specific topics.

### Key Concepts

- .NET implementations
    - .NET Framework
    - .NET Core
- The Common Language Runtime (CLR)
- Just-in-Time (JIT) compilation
- The Common Type Specification (CTS)
- .NET interoperability with native code
- Managed Modules
- Assemblies and references

### Reading Material

- _CLR via C#, Fourth Edition_: Pages 3-31
    - This section provides the most concise description available of the common language runtime's (CLR) execution model.
- _CLR via C#, Fourth Edition_: Pages 33-64
    - This section provides an in-depth coverage of _assemblies_ - the "logical executables" on which the various .NET runtime implementation operate.

### Optional Reading Material

- [MSDN: .NET Documentation](https://docs.microsoft.com/en-us/dotnet/standard/)
    - As mentioned in the introduction to this module, Microsoft is heavily invested in .NET. Accordingly, Microsoft's own documentation regarding .NET is remarkably lucid and well-maintained.
- _CLR via C#, Fourth Edition_: Pages 553-581
    - This section describes the methods by which standard Windows process come to host the CLR, as well as the fundamental security boundary enforced by the .NET Framework: AppDomains.
- _CLR via C#, Fourth Edition_: Pages 583-610
    - This section describes the process by which assembly references are resolved at load time and the fundamentals of runtime reflection within .NET applications.

### Exercises

- [Language Agnosticism of the CLR](./multilingual-assemblies)
- [Multimodule Assemblies](./multimodule-assemblies)

### Checks on Learning

- Name two distinct implementations of the .NET platform.
- What is the name of the runtime for the .NET Framework?
- What is the name of the runtime for .NET Core?
- What is the programming language on which the Common Language Runtime natively operates?
- What type of file is a _managed module_?
- In addition to Intermediate Language code, what else are compilers that target .NET required to emit into managed modules?
- What is the name of the module (dynamic library) that implements* the Common Language Runtime? 
- Describe the role of the Just-in-Time (JIT) compiler in the Common Language Runtime's execution model.
- What is meant by the statement that compilers that target .NET produce _safe_ code?
- What is the name of the collection of dynamic library assemblies that ships with the .NET Framework that contain core type definitions and functionality?
- From which type do all types that target the .NET Framework ultimately derive?
- What is the name of the formal specification that describes how types that target the Common Language Runtime behave?
- What is the difference between the CTS and the CLS?
- What is the name of the mechanism that allows managed code executing within the context of the Common Language Runtime to call native code (e.g. raw Win32 API functions)?
- What is the name of the additional metadata component that differentiates an assembly from a managed module?
- Do managed modules contain any metadata?
- Can the Common Language Runtime execute a managed module?
- Can the Common Language Runtime execute an assembly?
- Is it possible to build a new assembly without all of the files that implement a referenced assembly present?
- Is it possible to execute an assembly without all of the files that implement a referenced assembly present?

### Additional Notes

- *More accurately, this module actually acts as a _shim_ and determines the correct version of the CLR to load; the CLR itself is actually implemented as a COM server in a separate DLL, but this is beyond the scope of this module.