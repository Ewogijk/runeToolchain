# Contributing to runeToolchain

:tada: Welcome and thanks for taking the time to contribute to runeToolchain! :tada:

This document is a set of guidelines for contributing to runeToolchain, please take a moment to review it.
These guidelines are not rules, so feel free to propose changes in a pull request.


### Table of Contents

- [Found a Bug?](#found-a-bug)
- [Missing a Feature?](#missing-a-feature)
- [Submitting Issues](#submitting-issues)
- [Submitting a Pull Request](#submitting-a-pull-request)
- [Building the Project](#building-the-project)
  - [Getting the Dependencies](#getting-the-dependencies)
  - [Building the Toolchain](#building-the-toolchain)
  - [Navigating the Project](#navigating-the-project)
- [Styleguide](#styleguide)
    - [Commit Message Style](#commit-message-style)
    - [Code Style](#code-style)

## Found a Bug?

When you find a bug in the source code, you can help us by [submitting an issue](#submitting-issues)
or submit a [Pull Request](#submitting-a-pull-request) with the fix.


## Missing a Feature?

You can request the implementation of a new system call by 
[submitting an issue](#submitting-issues).


## Submitting Issues

Before submitting an issue please check the 
[Issue Tracker](https://github.com/Ewogijk/runeToolchain/issues) to make sure that your issue has 
not been reported yet. If your issue has already been reported, comment on the existing issue rather
than creating a new one.

You can submit a new issue by choosing one of the 
[Issue Templates](https://github.com/Ewogijk/runeToolchain/issues/new/choose) and filling out the 
template.

## Submitting a Pull Request

Before you submit your pull request (PR), please take a look at our guidelines, they help us to
ensure high quality and speed up the review:

- Search for an open [PR](https://github.com/Ewogijk/runeToolchain/pulls) that might relate to your 
    submission, so you don't work on an issue that someone already fixed.
- Follow our [Commit message style](#commit-message-style)
- Document your changes.
- Follow our [Code Style](#code-style).
- Send the Pull Request to `runeToolchain/main`.

Your first time contributing? Check out
[First Contributions](https://github.com/firstcontributions/first-contributions), it is great repo that guides you
through your first contribution.

After you submit the PR, we will review it and provide feedback. If we ask you to make changes to
your submission then make the required changes to your code and push them to your fork, your PR will
be updated automatically.

Once your PR gets accepted, we will merge it. That's it!


## Building the Project

### Getting the Dependencies

Building GCC and Binutils requires the following dependencies:
```shell
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
```

mlibc uses meson for building, so you will need to get it:

```shell
pip install scons click meson
```


### Building the Toolchain

You will need to build the freestanding and hosted compiler, both will make up the toolchain. First 
start with the freestanding compiler:

```shell
./Scripts/Build-Freestanding-Compiler.sh /path/to/your/systemroot num-make-jobs
```

This helper script will compile Binutils and GCC for you and install the binaries in your specified
system root. Similarly, build the hosted compiler: 

```shell
./Scripts/Build-Hosted-Compiler.sh /path/to/your/systemroot num-make-jobs
```

This script will, additionally to Binutils and GCC, compile mlibc and libstdc++-v3. Ember and 
Forge are shipped as part of mlibc.

Now grab a coffee or two while you are waiting for everything to be built.


### Navigating the Project

The project consists of three subprojects, use this overview to help you navigate the sources:

- `GCC/`: GCC 13.2.0 sources.
- `Binutils/`: Binutils 2.42 sources.
- `Scripts`: Build scripts.
- `LibC/`: mlibc sources.
  - `LibC/sysdeps/rune/`: This directory contains Ember, Forge and the integration with mlibc.


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

Our code formatter for C/C++ is `clang-format-19`, use it with the `.clang-format` config file in 
the project root directory.

Format the `SRC_FILES` with the following command:
```shell
clang-format-19 -i SRC_FILES
```

Naming conventions are not covered by clang-format, please adhere to the following guidelines:
- Classes/Structs/Enums/Namespaces: PascalCase
- Public member variables/Parameters/Local variables: snake_case
- Private member variables: _snake_case - Note the leading underscore e.g. _my_private_variable
- Global constants/Macros: SCREAMING_SNAKE_CASE
