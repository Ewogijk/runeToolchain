# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.6.0] - 2026-08-31

### 🐛 Bug Fixes

- :bug: Fix incorrect archive directory layout created by the release preparation script

### ♻️ Refactor

- :recycle: Integrate ThreadingBits kernel ABI changes

## [0.5.0] - 2026-08-28

### ✨ Features

- :sparkles: Integrate Ember KeyEvent API into Forge
- :sparkles: Add release preparation automation script
- :sparkles: Add commit of changelog and release tagging to release preparation script

### ♻️ Refactor

- :recycle: Upgrade to Docker Buildx

### 📝 Documentation

- :memo: Update changelog
- :memo: Update Issue templates

## [0.4.0] - 2026-05-23

### ✨ Features

- :sparkles: Update to GCC 16.1.0, Binutils 2.46, mlibc 6.3.1
- :sparkles: Add Docker-based build scripts for x86_64-elf and x86_64-rune targets
- :sparkles: Add git-cliff config file

### ♻️ Refactor

- :recycle: Improve logging

### 📝 Documentation

- :memo: Update CONTRIBUTING.md with arch linux instructions
- :memo: Update CONTRIBUTING.md with native and Docker-based build instructions

## [0.3.0] - 2025-12-15

### Added

- Update GCC sysroot to /opt/runeToolchain

## [0.2.0] - 2025-12-11

### Added

- Implement std::fstream support
- Implement std::file_system::directory_iterator support
- Implement std::file_system::create_directory support
- Add vfs_get_node_info_by_ID system call

## [0.1.0] - 2025-09-21

### Added

- Add 'x86_64-rune' target to GCC 13.2 and Binutils 2.42
- Add 'runeOS' support to mlibc
- Add VFS management system calls to Forge
- Add app management system calls to Forge
- Add memory management system calls to Forge
- Add multi-threading system calls to Forge
