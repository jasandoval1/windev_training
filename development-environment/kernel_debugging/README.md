## EXERCISE NAME

Install WinDbg as a kernel debugger

### Background

A majority of the concepts you will learn will be abstracted away by the operating system. We will learn to use a kernel debugger to look at the underlying structures Windows uses.

### Project Structure

Install a Kernel Debugger on a Virtual Machine (VM). This can be done using a physical host and a VM or VM to VM.

### Procedure

- Tools needed
Vmware Workstation/any virtualization software
Windows 10 SDK
Windows 10 VM


- From herein target will refer to the VM that will be debugged, the host is referred to as the VM running Windbg.
- Install the Windows 10 SDK on the host computer
- Establish a share from the target to the host `net use z: \\ip\c$`

On target computer open an ADMIN CMD and run the following commands
```
mkdir c:\KDNET
copy "Z:\Program Files (x86)\Windows Kits\10\Debuggers\x64\kdnet.exe c:\KDNET"
copy "Z:\Program Files (x86)\Windows Kits\10\Debuggers\x64\VerifiedNICList.xml c:\KDNET"
cd c:\KDNET
kdnet.exe
kdnet.exe HOSTIP 50000
```

Your ouput should look similiar to this
```
C:\KDNET>kdnet

Network debugging is supported on the following NICs:
busparams=11.0.0, Intel(R) 82574L Gigabit Network Connection, KDNET is running on this NIC.

C:\KDNET>kdnet.exe 192.168.111.129 50000

NtQuerySystemInformation cannot query SystemKernelDebuggingAllowed on this OS.
Enabling network debugging on Intel(R) 82574L Gigabit Network Connection.

To debug this machine, run the following command on your debugger host machine.
windbg -k net:port=50001,key=fbd6s5l1ggvi.3ht327jwm1xbs.2cgwi0jzi8xb9.17jc41w5ndod7

Then reboot this machine by running shutdown -r -t 0 from this command prompt.
```

Copy down the above windbg command

On host computer open an ADMIN CMD and run the following commands
```
"c:\Program Files (x86)\Windows Kits\10\Debuggers\x64\windbg.exe" -k net:port=50000,key=fbd6s5l1ggvi.3ht327jwm1xbs.2cgwi0jzi8xb9.17jc41w5ndod7
```

WinDbg should pop up and say 'Waiting to reconnect`

On target computer go ahead and reboot using `shutdown -r -t 0`

You should get a connection on your host box and be ready to debug.