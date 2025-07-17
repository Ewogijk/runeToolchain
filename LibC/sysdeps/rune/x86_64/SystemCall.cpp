
#include <Forge/SystemCall.h>

namespace Forge {
    S64 system_call0(U16 ID) {
        S64 ret = -1;
        __asm__ __volatile__ ("syscall" : "=a" (ret) : "a" (ID) : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call1(U16 ID, U64 arg1) {
        S64 ret = -1;
        __asm__ __volatile__ ("syscall" : "=a" (ret) : "a" (ID), "D" (arg1) : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call2(U16 ID, U64 arg1, U64 arg2) {
        S64 ret = -1;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2)
                : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call3(U16 ID, U64 arg1, U64 arg2, U64 arg3) {
        S64 ret = -1;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3)
                : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call4(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4) {
        S64 ret = -1;
        register U64 r8 __asm__("r8") = arg4;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8)
                : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call5(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4, U64 arg5) {
        S64 ret = -1;
        register U64 r8 __asm__("r8") = arg4;
        register U64 r9 __asm__("r9") = arg5;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8), "r" (r9)
                : "rcx", "r11", "memory");
        return ret;
    }


    S64 system_call6(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4, U64 arg5, U64 arg6) {
        S64 ret = -1;
        register U64 r8 __asm__("r8") = arg4;
        register U64 r9 __asm__("r9") = arg5;
        register U64 r10 __asm__("r10") = arg6;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8), "r" (r9), "r" (r10)
                : "rcx", "r11", "memory");
        return ret;
    }
}

