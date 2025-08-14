# runeToolchain

runeToolchain provides the compiler toolchain needed to build runeOS.

## What is in the Toolchain?

| Name         | Description                                                                                                                            |
|--------------|----------------------------------------------------------------------------------------------------------------------------------------|
| Freestanding | GCC compiler with x86_64-elf target used to compile the kernel sources. No standard library support.                                   |
| Hosted       | GCC compiler with x86_64-rune target used to compile userspace applications including runeOS. Features C/C++ standard library support. |
| Ember        | Ember provides the kernel ABI headers, they can be included with '#include <Ember/...>'                                                |
| Forge        | Forge is the system call library build on top of Ember. The Headers can be included with '#include <Forge/...>'.                       |

## Which standard library implementations are used?

[mlibc](https://github.com/managarm/mlibc) is a portable libc implementation of the Managarm project and acts as the
C runtime environment for userspace applications.

The [GNU C++ standard library](https://gcc.gnu.org/onlinedocs/libstdc++/) builds on top of libc and provides the
C++ standard library implementation.

## How much of the C standard is supported?

These standard library features are supported:

- Dynamic Memory
- Standard IO

The list of features will be extended in the future as the kernel will be further developed.

## How can I use the toolchain?

Download the latest release and unzip it at a location of your choice. Optionally, you can add the compilers to your
PATH environment variable, this is highly recommended. Now you are ready to use the toolchain.

Alternatively you can also build the toolchain yourself. To build the freestanding compiler run the following:

    ./Build-Freestanding-Compiler.sh /path/to/your/systemroot num-make-jobs

This helper script will compile Binutils and GCC for you. You can build the hosted compiler similarly:

    ./Build-Hosted-Compiler.sh /path/to/your/systemroot num-make-jobs

This script will, additionally to Binutils and GCC, compile mlibc and libstdc++-v3. Ember and Forge are shipped as part
of mlibc.

Now grab a coffee or two while you are waiting for everything to be built.

## Licensing

The project contains three directories each contains a subproject which has a license of their own. Check out the
COPYING/LICENSE file of the subprojects for details.

In short the subprojects are licensed as followed:

- GCC: GPL v3 or later
- Binutils: GPL v3 or later
- mlibc: MIT License