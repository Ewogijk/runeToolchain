
#ifndef RUNE_SYSCALLPANIC_H
#define RUNE_SYSCALLPANIC_H

/**
 * @brief Panic when a system call port is missing.
 * @param syscall Name of the missing system call.
 */
[[noreturn]] void forge_syscall_not_ported(const char* syscall);

#endif //RUNE_SYSCALLPANIC_H
