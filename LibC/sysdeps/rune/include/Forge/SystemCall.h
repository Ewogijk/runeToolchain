#ifndef FORGE_SYSTEMCALL_H
#define FORGE_SYSTEMCALL_H

#include <Ember/Ember.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                                          System Call Functions
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

namespace Forge {
    Ember::StatusCode system_call0(Ember::ResourceID ID);


    Ember::StatusCode system_call1(Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1
    	);


    Ember::StatusCode system_call2(Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2
    	);


    Ember::StatusCode system_call3(Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2,
    	Ember::SystemCallArgument arg3
    	);


    Ember::StatusCode system_call4(Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2,
    	Ember::SystemCallArgument arg3,
    	Ember::SystemCallArgument arg4
    	);


    Ember::StatusCode system_call5(Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2,
    	Ember::SystemCallArgument arg3,
    	Ember::SystemCallArgument arg4,
    	Ember::SystemCallArgument arg5
    	);


    Ember::StatusCode system_call6(
    	Ember::ResourceID ID,
    	Ember::SystemCallArgument arg1,
    	Ember::SystemCallArgument arg2,
    	Ember::SystemCallArgument arg3,
    	Ember::SystemCallArgument arg4,
    	Ember::SystemCallArgument arg5,
    	Ember::SystemCallArgument arg6
    	);
}


#endif //FORGE_SYSTEMCALL_H
