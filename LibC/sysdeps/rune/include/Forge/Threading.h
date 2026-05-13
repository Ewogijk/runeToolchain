#ifndef FORGE_THREADING_H
#define FORGE_THREADING_H

#include <Ember/Ember.h>

namespace Forge {

	/**
	 * If the mutex_name is an empty string then the kernel will choose a name for it.
	 *
	 * @brief Create mutex with the requested name.
	 * @param mutex_name   Name of the mutex.
	 * @return >0:       Mutex ID.<br>
	 *          BAD_ARG: The mutex name is null or exceeds the string size limit.<br>
	 *          FAULT:   Failed to create the mutex.
	 */
    Ember::StatusCode threading_mutex_create(const char* mutex_name);


	/**
	 * If the mutex is already locked the system call will block the calling thread until the mutex is unlocked.
	 *
	 * @brief Lock the mutex with the requested ID.
	 * @param ID         The ID of a mutex.
	 * @return OKAY:     The mutex got locked<br>
	 *          BAD_ARG: The ID is zero.<br>
	 *          UNKNOWN_ID:  No mutex with the requested ID was found.
	 */
    Ember::StatusCode threading_mutex_lock(U16 ID);


	/**
	 * If the mutex is not locked by the calling thread then this system call will do nothing.
	 *
	 * @brief Unlock the mutex with the requested ID.
	 * @param ID         The ID of a mutex.
	 * @return OKAY:     The mutex got locked<br>
	 *          BAD_ARG: The ID is zero.<br>
	 *          UNKNOWN_ID:  No mutex with the requested ID was found.
	 */
    Ember::StatusCode threading_mutex_unlock(U16 ID);


	/**
	 * @brief Free all resources associated with the requested mutex.
	 * @param ID         The ID of a mutex.
	 * @return OKAY:     The mutex got locked.<br>
	 *          BAD_ARG: The ID is zero.<br>
	 *          UNKNOWN_ID:  Failed to free the mutex.
	 */
    Ember::StatusCode threading_mutex_free(U16 ID);


	/**
	 * @brief Get the ID of the currently running thread.
	 * @return Success: The thread ID.
	 */
	Ember::StatusCode threading_get_thread_ID();


	/**
	 * @brief Set the current thread's thread control block.
	 * @param tcb A pointer to the thread control block.
	 * @return OKAY:     Success.<br>
	 *          BAD_ARG: The tcb buffer is null or in kernel memory.
	 */
	Ember::StatusCode threading_set_thread_control_block(void* tcb);
}

#endif //FORGE_THREADING_H
