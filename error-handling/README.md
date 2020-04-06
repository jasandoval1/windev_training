## Handling Errors in Windows Applications

This module will cover the essentials of the error handling facilities provided by the Win32 API as well as general strategies for managing error conditions when writing Windows applications.

### Key Concepts

- Windows error handling via `GetLastError()` and `FormatMessage()` usage
- Error code lookup options
- Structured Exception Handling (SEH) usage
- Error handling strategies (e.g. when to use SEH)
- Implementation details of Win32's `GetLastError()` function
- How Windows implements SEH

### Reading Material

- _Windows Via C/C++, Fifth Edition_: Pages 3-10
    - This section covers the essentials of dealing with errors reported by Win32 API calls.
- _Windows 10 System Programming_: "Handling API Errors"
    - This section provides a concise overview of several strategies for dealing with error conditions in Windows applications.
- _Windows System Programming, Fourth Edition_: Pages 101-126
    - This section covers the essentials of using the structured exception handling (SEH) facility provided by Windows.

### Optional Reading Material

- [External Article: A Crash Course on the Depths of Win32 Structured Exception Handling](http://bytepointer.com/resources/pietrek_crash_course_depths_of_win32_seh.htm)
    - The best article available for those wanting to understand the details of how SEH is implemented. Note, however, that the article is old (1997) and is thus specific to 32-bit versions of Windows.
- [External Video: Unwinding the Stack: Exploring How C++ Exceptions Work on Windows](https://www.youtube.com/results?search_query=james+mcnellis+unwind)
    - A video that nicely complements the article cited above with the additional benefit that it provides information regarding how language-specific exception implementations leverage the underlying SEH mechanism on Windows. Again, specific to 32-bit versions of Windows.
- [External Article: Exceptional Behavior: x64 Structured Exception Handling](http://www.osronline.com/article.cfm%5Earticle=469.htm)
    - Finally, an explanation of how 64-bit versions of MSVC implement SEH.

### Exercises

- [`GetLastError()` Internals](./get-last-error)

### Checks on Learning

- What is the difference between an SEH `__except` block and an SEH `__finally` block? 
- What are the valid options for return from an SEH filter expression?
- If one wraps the body of a while-loop in an SEH `__try` block, when is the corresponding `__finally` block executed? For instance: `while (...) __try { ... } __finally { ... }`
- Should SEH be utilized in C++ programs? Is it safe to mix use of both SEH and C++ exceptions?
- Where is the error code returned by a call to `GetLastError()` maintained? Why does it need to be maintained in this location?
- What is the effect of passing the following flags to `cl.exe`:
    - `/EHs`
    - `/EHa`
    - `/EHc`