## Windows Kernel Devlopment

This module builds on the knowledge of the Windows IO Subsystems acquired in the previous module by introducing the fundamentals of Windows driver development.

### Key Concepts

- Windows general purpose driver development models
    - Legacy/NT4 Model
    - Windows Driver Model (WDM)
    - Windows Driver Foundation (WDF) Model
- WDF Frameworks
    - User Mode Driver Framework (UMDF)
    - Kernel Mode Driver Framework (KMDF)
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

- Describe the purpose of a driver model.
- Why are drivers that adhere to the Legacy/NT4 driver model not suitable for supporting hardware devices?
- What are the two supporting facilities that differentiate the WDM driver model from the Legacy/NT4 model?
- What is the distinction between a _driver model_ and a _driver framework_?
- At a high level, how are the UMDF and KMDF implemented? 
- When is the `DRIVER_OBJECT` that represents a given driver instantiated in the lifetime of a driver?
- Device objects are always created by a driver via a call to `IoCreateDevice()`. When is this performed for Legacy/NT4 drivers? When is this performed for WDM drivers that participate in Plug-and-Play?
- Why is it often necessary for drivers that want to expose some interface to user-mode applications to create a symbolic link for the device(s) they manage?
- All IO operations on Windows are ultimately targeted at device objects (`DEVICE_OBJECT`s). However, user-mode applications typically acquire handles to file objects (`FILE_OBJECT`s) and initiate IO with these handles rather than doing so upon a handle to a device object. How does an IO request initially directed at a file object eventually reach the device object that it ultimately targets?
- What function does a driver call to complete an IO request?
- What function does a driver call to indicate that an IO request is pending and will be completed at a later time?   
- How does a driver determine the specific IO operation that is requested of it by an IRP?
- How is the data buffering method used in `IRP_MJ_READ` and `IRP_MJ_WRITE` IO requests determined?
- How is the data buffering method used in `IRP_MJ_DEVICE_CONTOL` IO requests determined?
- What is the structure used to lock pages in memory when direct IO is used?
- Who is responsible for copying the user-mode data buffer from user virtual address space to system virtual address space when buffered IO is used?
- Describe one instance in which direct IO should be used to transfer data between a user-mode application and a kernel driver.
- Describe on instance in which buffered IO should be used to transfer data between a user-mode application and a kernel driver.
- When is the driver unload routine called for a Legacy/NT4 driver? For a driver that participates in Plug-and-Play?