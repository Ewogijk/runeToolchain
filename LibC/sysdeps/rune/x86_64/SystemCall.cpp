
#include <Forge/SystemCall.h>

namespace Forge {
    Ember::StatusCode system_call0(Ember::ResourceID ID) {
        Ember::StatusCode ret = -1;
        __asm__ __volatile__ ("syscall" : "=a" (ret) : "a" (ID) : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call1(Ember::ResourceID ID, Ember::SystemCallArgument arg1) {
        Ember::StatusCode ret = -1;
        __asm__ __volatile__ ("syscall" : "=a" (ret) : "a" (ID), "D" (arg1) : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call2(Ember::ResourceID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2) {
        Ember::StatusCode ret = -1;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2)
                : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call3(Ember::ResourceID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3) {
        Ember::StatusCode ret = -1;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3)
                : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call4(Ember::ResourceID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3, Ember::SystemCallArgument arg4) {
        Ember::StatusCode ret = -1;
        register Ember::SystemCallArgument r8 __asm__("r8") = arg4;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8)
                : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call5(Ember::ResourceID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3, Ember::SystemCallArgument arg4, Ember::SystemCallArgument arg5) {
        Ember::StatusCode ret = -1;
        register Ember::SystemCallArgument r8 __asm__("r8") = arg4;
        register Ember::SystemCallArgument r9 __asm__("r9") = arg5;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8), "r" (r9)
                : "rcx", "r11", "memory");
        return ret;
    }


    Ember::StatusCode system_call6(Ember::ResourceID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3, Ember::SystemCallArgument arg4, Ember::SystemCallArgument arg5, Ember::SystemCallArgument arg6) {
        Ember::StatusCode ret = -1;
        register Ember::SystemCallArgument r8 __asm__("r8") = arg4;
        register Ember::SystemCallArgument r9 __asm__("r9") = arg5;
        register Ember::SystemCallArgument r10 __asm__("r10") = arg6;
        __asm__ __volatile__ ("syscall"
                : "=a" (ret)
                : "a" (ID), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r8), "r" (r9), "r" (r10)
                : "rcx", "r11", "memory");
        return ret;
    }
}

