
#ifndef RUNETOOLCHAIN_THREADING_H
#define RUNETOOLCHAIN_THREADING_H


#include <rune/TypeDef.h>


namespace Rune {
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Call IDs
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


    static constexpr U16 THREADING_MUTEX_CREATE  = 300;
    static constexpr U16 THREADING_MUTEX_LOCK    = 301;
    static constexpr U16 THREADING_MUTEX_UNLOCK  = 302;
    static constexpr U16 THREADING_MUTEX_RELEASE = 303;


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
}

#endif //RUNETOOLCHAIN_THREADING_H
