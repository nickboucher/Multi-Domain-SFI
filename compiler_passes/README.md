# Multi-Domain SFI Compiler Passes

This directory contains a set of clang compiler passes that will ultimately implement multi-domain SFI.

## Implementation Notes

The authors chose to implement multi-domain SFI as an LLVM compiler pass instead of a GCC extension because LLVM is generally easier to customize than GCC. However, it is worthwhile to note that some components of multi-domain SFI are not easy to implement in LLVM. Specifically, the components of multi-domain SFI which are assembly-language specific, such as instruction alignment, must be implemented as an LLVM backend rather than a compiler pass. This is notable more difficult.

In GCC, 32-byte basic block alignment could be achieved by simply passing `-falign-labels=32` to the compiler. However, even though alignment is already implemented on GCC but not on LLVM, LLVM is still the preferable compiler because the required custom components will be easier to write.

The current implementation is an example of how to mask all indirect memory write operation targets using a clang compiler pass. The code currently always masks target pointers with the value `0xFFFFFFFF` -- future work is needed to calculate the bitmask values as defined by the multi-domain SFI specification.

## Build Notes

In order to build the code in this repository, you must have `llvm` installed on your system *in addition* to `clang`, which often comes pre-installed on popular distros.

To build, run the following commands:
```bash
mkdir build && cd build
cmake ..
make
```
The resulting `.so` library file will be located in `build/lib`.

*Building on the latest version of OSX has proven to be difficult. Please consider building on a linux distro like Ubuntu.*

## Acknowledgements

The code for this implementation was influenced by previous work from:
- [Adrian Sampson](https://github.com/sampsyo/llvm-pass-skeleton/tree/mutate)
- [MemSentry](https://github.com/vusec/memsentry)
