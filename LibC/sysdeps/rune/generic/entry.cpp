#include <stdlib.h>
#include <stdint.h>

extern "C" void __dlapi_enter(uintptr_t *);
extern int main(int argc, char** argv, char** env);

extern "C" void __mlibc_entry(int argc, char** argv) {
    // Set up a fake linux stack with 0 CLI args and empty environ
    uintptr_t fake_entry_stack[4] = {
            0x0, // argc
            0x0, // argv
            0x0, // environ
            0x0  // auxv -> TODO can I leave this empty?
    };
    __dlapi_enter(fake_entry_stack);
    // rune Kernel does not support env vars atm
    char* env[1];
    env[0] = {
            nullptr
    };
    auto result = main(argc, argv, env);
    exit(result);
}
