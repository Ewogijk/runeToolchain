#include <Forge/Threading.h>

#include <Forge/SystemCall.h>

namespace Forge {
    int threading_mutex_create(const char* mutex_name) {
        return (int) system_call1(THREADING_MUTEX_CREATE, (uintptr_t) mutex_name);
    }


    int threading_mutex_lock(U16 handle) {
        return (int) system_call1(THREADING_MUTEX_LOCK, handle);
    }


    int threading_mutex_unlock(U16 handle) {
        return (int) system_call1(THREADING_MUTEX_UNLOCK, handle);
    }


    int threading_mutex_release(U16 handle) {
        return (int) system_call1(THREADING_MUTEX_UNLOCK, handle);
    }


	int threading_get_thread_ID() {
    	return static_cast<int>(system_call0(THREADING_GET_THREAD_ID));
    }


	int threading_get_thread_control_block(ThreadControlBlock* tcb_out) {
	    return static_cast<int>(
	    	system_call1(
	    		THREADING_GET_THREAD_CONTROL_BLOCK,
	    		reinterpret_cast<uintptr_t>(tcb_out)
	    		)
	    	);
    }

	int threading_set_thread_control_block(void* tcb) {
    	return static_cast<int>(
			system_call1(
				THREADING_SET_THREAD_CONTROL_BLOCK,
				reinterpret_cast<uintptr_t>(tcb)
				)
			);
    }
}
