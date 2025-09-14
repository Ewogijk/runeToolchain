# Contributing to runeToolchain

:tada: Welcome and thanks for taking the time to contribute to runeToolchain! :tada:

Please take a moment to review this document before starting to contribute. It is mostly a collection of guidelines that
intend to make working on the project easier for everyone.


### Table of Contents

- [Reporting Bugs](#reporting-bugs)
- [Requesting Features](#requesting-features)
- [Setting up your Local Development Environment](#setting-up-your-local-development-environment)
- [Building the Toolchain](#building-the-toolchain)
- [Styleguide](#styleguide)
    - [Commit Message Style](#commit-message-style)
    - [Code Style](#code-style)


## Reporting Bugs

You have found a bug and want to report it? This section will introduce our guidelines for bug reports, by following
them you help us to better understand your report and thus fixing your bug.

### Before Submitting

Please check the following guidelines before submitting, you may not need to create an issue if any of the following
points apply.

1. **Update to the latest release** - We may have already fixed your bug.
2. **Check the [Issue Tracker](https://github.com/Ewogijk/runeToolchain/issues)** - To see if the issue has already been
   reported. If it was and the issue is still open, comment on the existing issue rather than creating a new one.

### Submitting a Bug Report

To report a bug fill out the [Bug Report](https://github.com/Ewogijk/runeToolchain/issues/new/choose) template. Explain 
your problem as detailed as possible to help us track down your issue:

- **Use a clear and descriptive title**
- **Describe the steps to reproduce** - Be as detailed as possible. Explain not only what but also how you did
  something. Provide the arguments you used for functions and commands.
- **Explain the behavior after performing the steps**
- **Describe what behavior you expected**
- **Specify your environment** - Which runeToolchain release are you using.
- **Add screenshots or code snippets** if suitable


## Requesting Features

If you are missing the integration of a system call with Forge or the standard library, you are welcome to make a 
feature request!

### Before Submitting

Please check out the following guidelines before you submit your feature request to avoid creating duplicate requests:

1. **Make sure your feature is not already implemented** - If your feature is already implemented, check if your
   suggestion adds anything to the implementation. If yes, feel free to create an issue.
2. **Check the [Issue Tracker](https://github.com/Ewogijk/runeToolchain/issues)** - Your feature might have already been 
     requested. If that is the case, comment on the existing issue rather than creating a new one.
3. Make sure that [runeOS](https://github.com/Ewogijk/runeOS) Kernel supports the system call you want to be integrated.
    If not, make a feature request over there first.

### Submitting a Feature Request

To request a feature fill out the [Feature Request](https://github.com/Ewogijk/runeToolchain/issues/new/choose) 
template. Explain what your feature does and why you think it is important:

- **Use a clear and descriptive title**
- **Describe the feature or enhancement** - What problem does it solve? How does your solution look like? Why is it
  useful for the project?

## Setting up your Local Development Environment

Simply fork the repo and then clone your fork. If you are new to GitHub check out the 
[First Contributions](https://github.com/firstcontributions/first-contributions), it is a great repository to learn 
about pull requests which includes forking repositories.

Building GCC and Binutils requires the following dependencies:
```shell
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
```

mlibc uses meson for building, so you will need to get it:

```shell
pip install scons click meson
```

Our code formatter is `clang-format`, unfortunately the apt package of it is outdated. Run the following to get the
clang-format version compatible with the `.clang-format` config:

```shell
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 19
sudo apt install clang-format-19
```

The `Libc/sysdeps/rune` directory contains the relevant code, you can ignore the other directories. The Ember library is 
defined by the runeOS Kernel, it is not developed in this repo. The main development here is the integration of system 
calls with Forge and mlibc.


## Building the Toolchain

You will need to build the freestanding and hosted compiler, both will make up the toolchain. First start with the 
freestanding compiler:

```shell
./Scripts/Build-Freestanding-Compiler.sh /path/to/your/systemroot num-make-jobs
```

This helper script will compile Binutils and GCC for you and install the binaries in your specified system root. 
Similarly, build the hosted compiler: 

```shell
./Scripts/Build-Hosted-Compiler.sh /path/to/your/systemroot num-make-jobs
```

This script will, additionally to Binutils and GCC, compile mlibc and libstdc++-v3. Ember and Forge are shipped as part
of mlibc.

Now grab a coffee or two while you are waiting for everything to be built.


## Styleguide

### Commit Message Style

Follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) style:
- Use imperative, present tense
- Limit the first line to 50 characters or less
- Start your commit message with a [gitmoji](https://gitmoji.dev/) when you are...
    - :bug: `:bug:` - fixing a bug.
    - :sparkles:: `:sparkles:` - implementing a new feature or enhancement.
    - :memo:: `:memo:` - writing or updating documentation.
    - :fire:: `:fire:` - removing code or files.
    - :recycle:: `:recycle:` - refactoring code.

An example commit message could look like this:
```
✨: Add a feature

This feature solves this problem by doing this and that...

```

### Code Style

Our code formatter for C/C++ is `clang-format`, use it with the `.clang-format` config file in the project root
directory.

The following command will recursively format all .h/.cpp files in `SRC_DIR` with clang-format:
```shell
find SRC_DIR -name '*.h' -or -name '*.cpp' | xargs clang-format-19 -i
```

Naming conventions are not covered by clang-format, please adhere to the following guidelines:
- Classes/Structs/Enums/Namespaces: PascalCase
- Public member variables/Parameters/Local variables: snake_case
- Private member variables: _snake_case - Note the leading underscore e.g. _my_private_variable
- Global constants/Macros: SCREAMING_SNAKE_CASE

