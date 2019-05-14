# Multi-Domain SFI
An extension of Software Fault Isolation (SFI) which supports multiple isolation domains

*Nicholas Boucher, Harvard University*

## Overview

Software Fault Isolation, or SFI, is a set of well-defined, assembly-language-specific application binary restrictions which provide certain security guarantees. Specifically, SFI allows a single virtual address space to be partitioned into two domains such that each domain can only access memory within itself or via specific trampolines to the opposite domain. Multi-Domain SFI is a generalization of SFI that allows for up to `O(n)` unique isolation domains for any `n`-bit virtual address space.

## Paper

The paper fully describing multi-domain SFI can be found [here](paper/Multi%20Domain%20SFI.pdf).

## Implementation

Work is underway to implement multi-domain SFI as a set of LLVM passes for the `clang` compiler. This work is in its early stages and is not suitable for production. The ongoing work can be found in the [compiler passes](compiler_passes/) directory of this repository.

If you are interested in getting involved, please reach out via the contact tool on the author's personal [website](https://nicholas.bio/).
