## The I/O Subsystem and I/O Management APIs

This module dives into the nitty-gritty details of the Windows I/O subsystem; it reveals how the I/O operations that have been discussed extensively in previous sections are implemented under the hood withing the Windows Executive and Kernel.

### Reading Material

- _Windows Internals, Seventh Edition, Part 1_: Pages 483-552
    - This (extremely dense) section covers the core components of the I/O subsystem, including the I/O Manager, interrupt request levels (IRQLs) and deferred procedure calls (DPCs), the device driver taxonomy, and finally the details of I/O processing, from initiation to completion.
     