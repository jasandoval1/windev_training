## User Mode Security Mitigations

This module attempts to provide an overview of the many security measures and mitigations that Windows implements in, or that apply primarily to, user mode operations. This is an extremely broad and constantly-evolving topic to which the engineers at Microsoft are devoting considerable time and attention.

### Reading Material

- _The Rootkit Arsenal_: Pages 144-155
    - This section gives a brief overview of several imporant memory protection features: data execution prevention (hardware DEP), address space layout randomization (ASLR), "stack cookies" (the`/GS` compiler flag), and SEH handler overwrite prevention (the `/SAFESEH` linker flag).
- _Windows Internals, Seventh Edition, Part 1_: Pages 735-756
    - A superficial overview of process-level exploit mitigation policies applicable to user-mode applications.
  