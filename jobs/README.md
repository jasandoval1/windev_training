## Windows Jobs and the Job Management API

This section provides an overview of Windows jobs - a mechanism exposed by the Win32 API by which multiple processes may be logically grouped and managed collectively.

### Key Concepts

- The purpose of Windows jobs and the utility they provide
- Creating jobs
- Querying job properties
- Setting job properties and limits

### Reading Material

- _Windows 10 System Programming_: "Jobs"
    - This section provides a pragmatic overview of working with Windows job objects and how job objects may be utilized to exercise control over running programs that would otherwise be impossible.
- _Windows Internals, Seventh Edition, Part 1_: Pages 176-191
    - This section provides the conceptual background regarding Windows jobs and job objects.

### Exercises

- [Process Management with Jobs: UI Limitations](./ui-limits)

### Checks on Learning

- What is the Win32 API function one would use to create a new job?
- What is the Win32 API function one would use to open an existing job?
- Suppose _Process A_ wants to add _Process B_ to a job. What access rights must _Process A_ specify in a call to `OpenProcess()` in order to subsequently add _Process B_ to a job successfully?
- Is it possible for a process to belong to more than one job? What are the implications of this?
- What is one system property that may be controlled via job objects that is otherwise inaccessible?
