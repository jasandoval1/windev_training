## The .NET Framework and Managed Application Execution Model

This module provides a (brief) introduction to the .NET Framework and the execution model utilized by managed applications - applications that target the .NET Framework. While the .NET Framework is but one among many technologies built on top of the Windows operating system, it is one that holds a privileged place in the hearts and minds of Microsoft's engineers and Windows application developers alike; a passing familiarity with the framework is a necessary precondition for understanding many of the design decisions introduced in recent versions of Windows.

### Reading Material

- _CLR via C#, Fourth Edition_: Pages 3-31
    - This section provides the most concise description available of the common language runtime's (CLR) execution model.

### Optional Reading Material

- _CLR via C#, Fourth Edition_: Pages 553-581
    - This section describes the methods by which standard Windows process come to host the CLR, as well as the fundamental security boundary enforced by the .NET Framework: AppDomains.
- _CLR via C#, Fourth Edition_: Pages 583-610
    - This section describes the process by which assembly references are resolved at load time and the fundamentals of runtime reflection within .NET applications.