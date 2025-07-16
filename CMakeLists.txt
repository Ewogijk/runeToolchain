cmake_minimum_required(VERSION 3.26)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(runeToolChain)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/LibC/sysdeps/rune/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/ansi/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/bsd/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/elf/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/glibc/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/internal/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/linux/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/lsb/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/posix/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/options/rtld/include)
include_directories(${PROJECT_SOURCE_DIR}/LibC/subprojects/frigg/include)

add_executable(runeToolChain LibC/sysdeps/rune/generic/entry.cpp
        LibC/sysdeps/rune/generic/entry.cpp
        LibC/options/ansi/generic/stdlib.cpp
        LibC/sysdeps/rune/generic/sysdeps.cpp
        LibC/options/rtld/generic/main.cpp)
set_target_properties(runeToolChain PROPERTIES LINKER_LANGUAGE CXX)
