## Windows Developer Training Outline

_Updated: March, 2020_

### Overview

This repository contains an outline a training curriculum designed to develop (pun intended) aspiring Windows developers.

The outline provided herein assumes the following background knowledge and skills:
- Working proficiency in the C programming language
- Operating system concepts including:
    - Virtual memory, paging, and address translation
    - Processes and threads
    - CPU scheduling
    - The distinction between user-mode and kernel-mode
    - Filesystems

The training curriculum is organized as a logical progression of topics relevant to Windows development - the material included in module N assumes mastery of the material presented in module N-1. That said, if you are coming to this repository with some degree of background in development on the Windows platform, you may feel comfortable skipping some number of modules. 

Each module is partitioned into one or more training items. Each of these training items is composed of relevant reading material and, where applicable, one or more programming exercises or "experiments" designed to reinforce the concepts presented in the reading.

Happy hacking.

### Training Modules

- [Introduction to Programming on Windows and the Win32 API](./introduction)
- [Setting up a Development Environment: Visual Studio](./development-environment)
- [Working with Strings and Text](./strings-and-text)
- [Handling Errors in Windows Applications](./error-handling)
- [Essential Input / Output Operations](./user-io)
- [Windows System Architecture](./system-architecture)
- [Windows Kernel Objects and the Windows Object Manager](./object-manager)
- [Windows Processes and the Process Management API](./processes)
- [Windows Jobs and the Job Management API](./jobs)
- [Windows Threads and the Thread Management API](./threads)
- [Synchronization in User Mode](./user-synchronization)
- [Synchronization with Kernel Objects](./kernel-synchronization)
- [Advanced IO Operations in User Mode](./advanced-io)
- [Interprocess Communication](./interprocess-communication)
- [The Windows Memory Management Subsystem and the Memory Management API](./memory-subsystem)
- [The Portable Executable File Format](./pe-format)
- [Loading and Executing a Windows Executable](./pe-execution)
- [Dynamic Link Libraries](./dynamic-libraries)
- [Windows Service Applications](./services)
- [System Service Dispatching on Windows](./system-service-dispatching)
- [The Windows Security Model and Programming Windows Security](./security-model)
- [Network Programming on Windows](./networking)
- [Windows Management Mechanisms](./management-mechanisms)
- [The Windows Boot Process and System Initialization](./boot-process)
- [User Mode Security Mitigations](./user-security-mitigations)
- [Kernel Mode Security Mitigations](./kernel-security-mitigations)
- [The IO Subsystem and IO Management APIs](./io-subsystem)
- [Windows Kernel Development](./kernel-development)
- [The Windows Hypervisor and Virtualization Based Security](./virtualization)

### Required Materials

The list below enumerates the major reading materials referenced throughout this guide:

- _Windows System Programming, Fourth Edition_ By Johnson M. Hart
- _Windows Via C/C++, Fifth Edition_ by Jeffrey Richter and Christophe Nasarre
- _Windows Internals, Seventh Edition, Part 1_ by Yosifovich et. al.
- _Windows Internals, Seventh Edition, Part 2_ by Russinovich et. al. (forthcoming)
- _Windows Internals, Sixth Edition, Part 1_ by Russinovich et. al.
- _Windows Internals, Sixth Edition, Part 2_ by Russinovich et. al.
- _Windows 10 System Programming_ by Pavel Yosifovich
- _Professional Visual Studio 2017_ by Bruce Johnson
- _Windows Kernel Programming_ by Pavel Yosifovich
- _The Rootkit Arsenal, Second Edition_ by Reverend Bill Blunden
- _Rootkits and Bootkits_ by Matrosov et. al.

In addition to these primary references, additional materials may be listed under the reading materials for a particular topic. In these cases, a mechanism to access the cited material will be provided.
