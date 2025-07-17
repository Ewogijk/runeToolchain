#include <Forge/SystemCallPanic.h>

#include <Forge/App.h>


[[noreturn]] void forge_syscall_not_ported(const char* syscall) {
    Forge::app_write_stderr("Missing system call port: ");
    Forge::app_write_stderr(syscall);
    Forge::app_exit(-1);
}
