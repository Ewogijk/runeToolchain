#include <Forge/Panic.h>

#include <Forge/Utility.h>

#include <Forge/App.h>

namespace Forge {
	[[noreturn]] void syscall_not_ported(const char* syscall) {
		const auto prefix = "Missing system call port: ";
		Forge::app_write_stderr(prefix, Forge::strlen(prefix));
		Forge::app_write_stderr(syscall, strlen(syscall));
		Forge::app_exit(-1);
	}
}

