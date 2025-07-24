#ifndef RUNETOOLCHAIN_THREADING_H
#define RUNETOOLCHAIN_THREADING_H


#include <Forge/TypeDef.h>


namespace Forge {
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Call IDs
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


    static constexpr U16 THREADING_MUTEX_CREATE  = 300;
    static constexpr U16 THREADING_MUTEX_LOCK    = 301;
    static constexpr U16 THREADING_MUTEX_UNLOCK  = 302;
    static constexpr U16 THREADING_MUTEX_RELEASE = 303;
	static constexpr U16 THREADING_GET_THREAD_ID = 304;
	static constexpr U16 THREADING_GET_THREAD_CONTROL_BLOCK = 305;
	static constexpr U16 THREADING_SET_THREAD_CONTROL_BLOCK = 306;


	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	//                                          Data Definitions
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


	/**
	 * @brief Information about a thread for user space.
	 */
	struct ThreadControlBlock {
		U16 thread_ID;
		void* stack_addr;
		size_t stack_size;
	};


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Calls
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    /**
    * If the mutex_name is an empty string then the kernel will choose a name for it.
    *
    * @brief Create mutex with the requested name.
    * @param mutex_name   Name of the mutex.
    * @return >0: Handle to the mutex.
    *          -1: The mutex name is null or exceeds the maximum length of 128 bytes.
    *          -2: Failed to create the mutex.
    */
    int threading_mutex_create(const char* mutex_name);


    /**
     * If the mutex is already locked the system call will block the calling thread until the mutex is unlocked.
     *
     * @brief Lock the mutex with the requested handle.
     * @param handle       The handle of a mutex.
     * @return 0: The mutex got locked
     *          -1: The handle is zero.
     *          -2: No mutex with the requested handle was found.
     */
    int threading_mutex_lock(U16 handle);


    /**
     * If the mutex is not locked by the calling thread then this system call will do nothing.
     *
     * @brief Unlock the mutex with the requested handle.
     * @param handle       The handle of a mutex.
     * @return 0: The mutex got locked
     *          -1: The handle is zero.
     *          -2: No mutex with the requested handle was found.
     */
    int threading_mutex_unlock(U16 handle);


    /**
     * @brief Free all resources associated with the mutex with the requested handle.
     * @param handle       The handle of a mutex.
     * @return 0: The mutex got locked
     *          -1: The handle is zero.
     *          -2: Failed to release the mutex.
     */
    int threading_mutex_release(U16 handle);


	/**
	 * @brief Get the ID of the currently running thread.
	 * @return 0: Success.
	 *          -1: The ID_out buffer is null or in kernel memory.
	 */
	int threading_get_thread_ID();


	/**
	 * @brief Get the thread control block of the currently running thread.
	 * @param tcb_out      Thread control block buffer.
	 * @return 0: Success.
	 *          -1: The tcb_out buffer is null or in kernel memory.
	 */
	int threading_get_thread_control_block(ThreadControlBlock* tcb_out);

	/**
	 * @brief Set the current thread's thread control block.
	 * @param tcb          A pointer to the thread control block.
	 * @return 0: Success.
	 *          -1: The tcb buffer is null or in kernel memory.
	 */
	int threading_set_thread_control_block(void* tcb);
}

#endif //RUNETOOLCHAIN_THREADING_H
