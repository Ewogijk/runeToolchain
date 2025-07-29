
#ifndef FORGE_PANIC_H
#define FORGE_PANIC_H

/**
 * @brief Panic when a system call port is missing.
 * @param syscall Name of the missing system call.
 */
[[noreturn]] void forge_syscall_not_ported(const char* syscall);

#endif //FORGE_PANIC_H
