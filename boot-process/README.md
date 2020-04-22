## The Windows Boot Process and System Initialization

This module explores the boot process utilized by Windows systems in the desktop environment - the process may differ markedly on other form factors on which the Windows One Core OS runs such as IOT devices or XBox gaming consoles. 

Note that this module only scratches the surface of this topic. The full story of the boot process on modern computing systems (Windows or otherwise) is far more complex than the model described here and could easily consume an entire training curriculum on its own. For instance, some of the important boot-process related topics _not_ covered in this module include:

- Master Boot Record (MBR) versus GUID Partition Table (GPT) drive formatting
- Platform secure boot technology (e.g. Intel BootGuard, ARM Trusted Boot)
- The Unified Extensible Firmware Interface (UEFI) boot sequence and UEFI secure boot 
- Boot-time kernel code signature verification and OS secure boot
- Boot-time kernel driver signature enforcement
- Windows Early-Launch Anti-Malware driver loading and operation
- Windows boot process under Virtualization-Based Security (VBS) protection

Don't fret. We'll get to the above topics eventually, but first, the basics.

### Key Concepts

- Legacy BIOS versus UEFI firmware boot environments
- The Windows boot manager
- The Windows boot loader
- Drivers and Windows services automatically started during the boot process
- Session initialization
- Subsystem initialization
- Windows boot process security considerations 

### Reading Material

- _The Rootkit Arsenal_: Pages 174-186
    - This section provides an overview of the OS boot process from the BIOS / UEFI firmware handoff through the logon process and execution of the interactive user's shell. 
- _Rootkits and Bootkits_: Pages 57-68
    - This section introduces the basic concepts of generic OS boot procedures, and subsequently details some procedures specific to Windows systems.

### Optional Reading Material

- _Rootkits and Bootkits_: Pages 233-254
    - This section introduces the UEFI boot process and the numerous ways in which it differs from the legacy BIOS boot process with which we are familiar.
- _Rootkits and Bootkits_: Pages 319-350
    - This section explores the UEFI Secure Boot process - it takes us from platform secure boot (e.g. Intel BootGuard) all the way through the firmware handoff to the operating system boot manager. Be warned: this topic is deceptively complex and constantly changing.
- [Channel9: Boot Environment](https://channel9.msdn.com/Shows/Going+Deep/Inside-Windows-8-Chris-Stevens-Boot-Environment)
    - An extended interview with one of the Microsoft engineers that worked on the many changes to the boot process that Windows introduced in Windows 8.

### Checks on Learning

- On legacy BIOS systems, what is the first code executed outside of the BIOS firmware? From what location is this code loaded?
- On a UEFI system, what is the first code executed outside of the UEFI firmware? From what location is this code loaded?
- What is the name of the file that implements the Windows boot manager on legacy BIOS systems? What type of executable image is this?
- What is the name of the file that implements the Windows boot manager on UEFI systems? What type of executable is this?
- Regardless of the firmware implementation (BIOS or UEFI) the Windows boot manager requires  configuration data to manage the boot process. From what location does the boot manager read this configuration data?
- Describe two (2) BCD boot variables that are of interest in the context of boot process subversion.
- What is the difference between the Windows boot manager and the Windows boot loader?
- What is the name of the file that implements the Windows boot loader on legacy BIOS systems?
- What is the name of the file that implements the Windows boot loader on UEFI systems?
- How would you view the boot configuration on a modern (Vista and later) Windows system?
- At what point in the boot process are boot-start drivers loaded? By which program?
- At what point in the boot process are system-start drivers loaded? By which program?
- On Windows desktop systems, there are typically two active sessions running: session 0 and session 1 (you can confirm this with a tool such as `winobj.exe` from SysInternals). If there are only two active sessions, why is it the case that there are typically three instances of `smss.exe` running on such systems?
- On a Windows desktop system with two active sessions, session 0 and session 1, how many instances of the `csrss.exe` process would you expect to find running?
- At what point in the boot process are auto-start (`SERVICE_AUTO_START`) system services started? Which program performs this initialization?
- A number of the above questions focus on services and drivers that are automatically loaded and executed by the system at some point during boot and early system initialization. Why do you think such attention is paid to these programs - in the context of OS security subversion, why are such observations relevant?
