#include <Forge/Threading.h>

#include <Ember/SystemCallID.h>

#include <Forge/SystemCall.h>

namespace Forge {
    Ember::StatusCode threading_mutex_create(const char* mutex_name) {
        return system_call1(Ember::Threading::MUTEX_CREATE, reinterpret_cast<uintptr_t>(mutex_name));
    }


    Ember::StatusCode threading_mutex_lock(const U16 ID) {
        return system_call1(Ember::Threading::MUTEX_LOCK, ID);
    }


    Ember::StatusCode threading_mutex_unlock(const U16 ID) {
        return system_call1(Ember::Threading::MUTEX_UNLOCK, ID);
    }


    Ember::StatusCode threading_mutex_free(const U16 ID) {
        return system_call1(Ember::Threading::MUTEX_FREE, ID);
    }


	Ember::StatusCode threading_get_thread_ID() {
    	return system_call0(Ember::Threading::THREAD_GET_ID);
    }

	Ember::StatusCode threading_set_thread_control_block(void* tcb) {
    	return system_call1(
		    Ember::Threading::THREAD_CONTROL_BLOCK_SET,
		    reinterpret_cast<uintptr_t>(tcb)
	    );
    }
}
