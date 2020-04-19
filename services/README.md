## Windows Service Applications

This module introduces Windows service applications - a special kind of user-mode application imbued with semantics that are distinct from typical user-mode applications.

### Key Concepts 

- Service Applications
- Service Control Programs
- The Service Control Manager
- Implementing Service Applications
- Implementing Service Control Programs
- Security implications of Windows services

### Reading Material

- _Windows System Programming, Fourth Edition_: Pages 453-480
    - This section provides both conceptual background on Windows services including their role in the context of the overall operating system as well as practical guidance on writing Windows service applications and the special requirements involved therein.
- _Windows Internals, Sixth Edition, Part 1_: Pages 305-335
    - This section provides a more in-depth conceptual background regarding service applications and their interaction with the service control manager (SCM). 

### Checks on Learning

- What is the difference between a _Service Application_ and a _Service Control Program_?
- What are the three (3) primary built-in Windows accounts under which services execute?
- Describe the distinction between a Service Application and a _logical service_. 
- Describe the difference between services that specify the `SERVICE_WIN32_OWN_PROCESS` type versus those that specify the `SERVICE_WIN32_SHARE_PROCESS` type.
- How is a Windows service started? How is it stopped?
- Under what conditions does the `main()` function of a Service Application return?
- How many distinct control signals may the Service Control Manager deliver to a Windows service? Is it necessary for a Windows service to handle all of these possible signals?
- Sharing kernel objects between Windows services and standard application presents a security concern because Windows services often execute in the context of privileged accounts. Describe one other consideration that complicates the practice of sharing kernel objects between services and standard user applications.
- How does the Service Control Manager listen for requests from Service Control Programs?
- How does the Service Control Manager communicate with individual Windows services?
- How would you list all currently active services on a system from the Windows commandline?
- How many logical services does the `lsass.exe` process host? What are they?
- Suppose the service _Service A_ is registered on a system via a call to `CreateService()`. At what registry location is the configuration data for _Service A_ persisted?