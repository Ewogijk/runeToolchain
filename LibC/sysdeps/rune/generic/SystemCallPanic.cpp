#include <rune/SystemCallPanic.h>

#include <rune/App.h>


[[noreturn]] void rune_syscall_not_ported(const char* syscall) {
    Rune::app_write_stderr("Missing system call port: ");
    Rune::app_write_stderr(syscall);
    Rune::app_exit(-1);
}
