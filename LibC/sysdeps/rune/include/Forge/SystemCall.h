#ifndef FORGE_SYSTEMCALL_H
#define FORGE_SYSTEMCALL_H

#include <Ember/StatusCode.h>
#include <Ember/SystemCallID.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                                          System Call Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

namespace Forge {
    Ember::StatusCode system_call0(Ember::SystemCallID ID);


    Ember::StatusCode system_call1(Ember::SystemCallID ID, Ember::SystemCallArgument arg1);


    Ember::StatusCode system_call2(Ember::SystemCallID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2);


    Ember::StatusCode system_call3(Ember::SystemCallID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3);


    Ember::StatusCode system_call4(Ember::SystemCallID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3, Ember::SystemCallArgument arg4);


    Ember::StatusCode system_call5(Ember::SystemCallID ID, Ember::SystemCallArgument arg1, Ember::SystemCallArgument arg2, Ember::SystemCallArgument arg3, Ember::SystemCallArgument arg4, Ember::SystemCallArgument arg5);


    Ember::StatusCode system_call6(
    	Ember::SystemCallID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2,
    	Ember::SystemCallArgument arg3,
    	Ember::SystemCallArgument arg4,
    	Ember::SystemCallArgument arg5,
    	Ember::SystemCallArgument arg6
    	);
}


#endif //FORGE_SYSTEMCALL_H
