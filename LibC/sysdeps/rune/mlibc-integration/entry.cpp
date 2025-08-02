#include <stdlib.h>
#include <stdint.h>
#include <elf.h>

struct StartInfo;

using U64 = uint64_t;
using ThreadMain = int (*)(StartInfo*);

struct StartInfo {
	/**
	 * @brief Number of arguments.
	 */
	int argc;

	/**
	 * @brief A null terminated array of string arguments.
	 */
	char** argv;

	/**
	 * @brief Low and high bytes of a random 16 byte value.
	 */
	U64 random_low;
	U64 random_high;

	/**
	 * @brief Virtual address of an array where the ELF program headers are stored.
	 */
	void* program_header_address;

	/**
	 * @brief Size of a program header.
	 */
	size_t program_header_size;

	/**
	 * @brief Size of the program header array.
	 */
	size_t program_header_count;

	/**
	 * @brief Main function of the thread.
	 */
	ThreadMain main;

	/**
	 * @brief Address of a 16 byte random value.
	 */
	void* random;
};

extern "C" void __dlapi_enter(uintptr_t *);
extern int main(int argc, char** argv, char** env);

extern "C" void __mlibc_entry(StartInfo* start_info) {
	// Linux provides this stack to userspace programs and mlibc also expects this
	// We will pass a fake stack with this layout to mlibc
	// |		Stack			|
	// |------------------------|
	// |	  argc				|
	// |	  argv[0]			|
	// |		.				|
	// |		.				|
	// |		.				|
	// |	  argv[argc - 1]	|
	// |	  nullptr			|
	// |	  environ[0]		|
	// |		.				|
	// |		.				|
	// |		.				|
	// |	  environ[n]		|
	// |	  nullptr			|
	// |	  auxval[0]			|
	// |		.				|
	// |		.				|
	// |		.				|
	// |	  auxval[m]			|
	// Create fake stack with space for argc, argv and a subset of the auxiliary vector
	// environ is not supported atm
	// Supported auxiliary vector keys: AT_PHDR, AT_PHENT, AT_PHNUM, AT_ENTRY, AT_EXECFN,
	//									AT_RANDOM, AT_SECURE, AT_NULL
	size_t argv_size = start_info->argc + 1; // include null terminator
	size_t environ_size = 1; // null terminator
	size_t auxv_size = 16; // key-value pairs
	uintptr_t fake_entry_stack[1 + argv_size + environ_size + auxv_size];
	fake_entry_stack[0] = start_info->argc;
	for (int i = 0; i < start_info->argc; i++)
		fake_entry_stack[1 + i] = reinterpret_cast<uintptr_t>(start_info->argv[i]);
	fake_entry_stack[1 + argv_size - 1] = 0;
	fake_entry_stack[1 + argv_size + environ_size - 1] = 0;

	fake_entry_stack[(1 + argv_size + environ_size)] = AT_PHDR;
	fake_entry_stack[(1 + argv_size + environ_size) + 1] = reinterpret_cast<uintptr_t>(start_info->program_header_address);
	fake_entry_stack[(1 + argv_size + environ_size) + 2] = AT_PHENT;
	fake_entry_stack[(1 + argv_size + environ_size) + 3] = start_info->program_header_count;
	fake_entry_stack[(1 + argv_size + environ_size) + 4] = AT_PHNUM;
	fake_entry_stack[(1 + argv_size + environ_size) + 5] = start_info->program_header_size;
	fake_entry_stack[(1 + argv_size + environ_size) + 6] = AT_ENTRY;
	fake_entry_stack[(1 + argv_size + environ_size) + 7] = reinterpret_cast<uintptr_t>(start_info->main);
	fake_entry_stack[(1 + argv_size + environ_size) + 8] = AT_EXECFN;
	fake_entry_stack[(1 + argv_size + environ_size) + 9] = reinterpret_cast<uintptr_t>(start_info->argv[0]);
	fake_entry_stack[(1 + argv_size + environ_size) + 10] = AT_RANDOM;
	fake_entry_stack[(1 + argv_size + environ_size) + 11] = reinterpret_cast<uintptr_t>(start_info->random);
	fake_entry_stack[(1 + argv_size + environ_size) + 12] = AT_SECURE;
	fake_entry_stack[(1 + argv_size + environ_size) + 13] = 0; // Disabled, not supported
	fake_entry_stack[(1 + argv_size + environ_size) + 14] = AT_NULL;
	fake_entry_stack[(1 + argv_size + environ_size) + 15] = 0;

    __dlapi_enter(fake_entry_stack);
    // rune Kernel does not support env vars atm
    char* env[1];
    env[0] = {
            nullptr
    };
    auto result = main(start_info->argc, start_info->argv, env);
    exit(result);
}
