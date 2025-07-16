
#ifndef RUNE_SYSTEMCALL_H
#define RUNE_SYSTEMCALL_H

#include <rune/TypeDef.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                                          System Call IDs
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//




// VFS System Calls



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                                          System Call Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

namespace Rune {
    S64 system_call0(U16 ID);


    S64 system_call1(U16 ID, U64 arg1);


    S64 system_call2(U16 ID, U64 arg1, U64 arg2);


    S64 system_call3(U16 ID, U64 arg1, U64 arg2, U64 arg3);


    S64 system_call4(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4);


    S64 system_call5(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4, U64 arg5);


    S64 system_call6(U16 ID, U64 arg1, U64 arg2, U64 arg3, U64 arg4, U64 arg5, U64 arg6);
}


#endif //RUNE_RUNE_SYSTEMCALL_H
