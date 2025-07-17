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
}
