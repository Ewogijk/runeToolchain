.section .text
.global _start
_start:
    # ABI: rdi=argc, rsi=argv
	call __mlibc_entry

.section .note.GNU-stack,"",%progbits

