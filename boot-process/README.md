## The Windows Boot Process and System Initialization

This module explores the boot process utilized by Windows systems in the desktop environment - the process may differ markedly on other form factors on which the Windows One Core OS runs such as IOT devices or XBox gaming consoles. 

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