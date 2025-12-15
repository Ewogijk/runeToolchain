# runeToolchain

runeToolchain provides the compiler toolchain needed to build runeOS.

## What is in the Toolchain?

| Name            | Description                                                                                                                            |
|-----------------|----------------------------------------------------------------------------------------------------------------------------------------|
| x86_64-elf GCC  | GCC compiler with x86_64-elf target used to compile the kernel sources. No standard library support.                                   |
| x86_64-rune GCC | GCC compiler with x86_64-rune target used to compile userspace applications including runeOS. Features C/C++ standard library support. |
| Ember           | Ember provides the kernel ABI headers, they can be included with '#include <Ember/...>'                                                |
| Forge           | Forge is the system call library build on top of Ember. The Headers can be included with '#include <Forge/...>'.                       |

## Which standard library implementations are used?

[mlibc](https://github.com/managarm/mlibc) is a portable libc implementation of the Managarm project
and acts as the
C runtime environment for userspace applications.

The [GNU C++ standard library](https://gcc.gnu.org/onlinedocs/libstdc++/) builds on top of libc and
provides the
C++ standard library implementation.

## How much of the C standard is supported?

These standard library features are supported:

- Dynamic Memory
- Standard IO

The list of features will be extended in the future as the kernel will be further developed.

## How can I use the toolchain?

Either download the latest release which contains precompiled binaries for Ubuntu 24.04 and then
extract the zip to the `/opt` directory.

Or build the toolchain yourself, checkout the
[Contribution Guidelines](CONTRIBUTING.md#building-the-project) for the details on how to build it.
