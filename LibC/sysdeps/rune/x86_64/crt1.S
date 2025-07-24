.section .text
.global _start
_start:
    # ABI: rdi=start_info
	call __mlibc_entry

.section .note.GNU-stack,"",%progbits

