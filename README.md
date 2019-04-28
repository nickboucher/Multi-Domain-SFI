# Multi-Domain-SFI
An extension of Software Fault Isolation (SFI) which supports multiple isolation domains

*Nicholas Boucher, Harvard University*

Software Fault Isolation, or SFI, is a set of well-defined, assembly-language-specific application binary restrictions which provide certain security guarantees. Specifically, SFI allows a single virtual address space to be partitioned into two domains such that each domain can only access memory within itself or via specific trampolines to the opposite domain. Multi-Domain SFI is a generalization of SFI that allows for up to `O(n)` unique isolation domains for any `n`-bit virtual address space.

The paper fully describing multi-domain SFI can be found [here](paper/Multi Domain SFI.pdf).
