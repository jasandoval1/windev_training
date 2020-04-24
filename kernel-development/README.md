## Windows Kernel Devlopment

This module builds on the knowledge of the Windows IO Subsystems acquired in the previous module by introducing the fundamentals of Windows driver development.

### Key Concepts

- Windows driver development models
    - Legacy Model
    - Windows Driver Model (WDM)
    - Windows Driver Foundation (WDF) Models
- Critical IO Manager data structures
    - Driver Object
    - Device Object
    - File Object
- Driver entry point
- Driver major and minor function tables
- Driver unloading
- IO buffering methods
    - Buffered IO
    - Direct IO
    - Neither IO

### Reading Material

- _Windows Internals, Seventh Edition Part 1_: Pages 498-510
    - This section provides a brief overview of the major players in Windows driver development, including the primary routines defined by device drivers (under the legacy driver model), driver objects, device objects, and file objects.
- _Windows Internals, Seventh Edition Part 1_: Pages 528-533
    - This section covers the basics of the various IO methods available to Windows driver developers and the critical distinction between low-IRQL and high-IRQL synchronization mechanisms.

### Optional Reading Material

- _Windows Kernel Programming_
    - Yes, the lack of a page number specification on the line above is deliberate; this entire book is devoted to developing Windows kernel drivers, specifically in the legacy software driver and filesystem minifilter models. The theory in this book is sparse, but the author makes up for this with an impressive number of involved sample applications and projects.

### Checks on Learning