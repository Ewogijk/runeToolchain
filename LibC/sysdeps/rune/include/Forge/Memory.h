
#ifndef RUNETOOLCHAIN_MEMORY_H
#define RUNETOOLCHAIN_MEMORY_H


#include <Forge/TypeDef.h>


namespace Forge {
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Call IDs
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    // Memory Management System Calls
    static constexpr U16 MEMORY_GET_PAGE_SIZE = 0;
    static constexpr U16 MEMORY_ALLOCATE_PAGE = 1;
    static constexpr U16 MEMORY_FREE_PAGE     = 2;


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          Data Definitions
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    /**
     * @brief Return codes for "memory_map" in case of failure.
     * <ul>
     *  <li>BAD_ADDRESS: The requested memory region intersects kernel memory.</li>
     *  <li>BAD_PAGE_PROTECTION: Unknown page protection flags where given.</li>
     *  <li>MEM_MAP_BAD_ALLOC: The mapping of the memory region failed.</li>
     * </ul>
     */
    static uintptr_t MEM_MAP_BAD_ADDRESS         = (uintptr_t) (void*) -1;
    static uintptr_t MEM_MAP_BAD_PAGE_PROTECTION = (uintptr_t) (void*) -2;
    static uintptr_t MEM_MAP_BAD_ALLOC           = (uintptr_t) (void*) -3;


    /**
     * @brief Describes page protection levels.
     * <ul>
     *  <li>READ: The page can only be read.</li>
     *  <li>WRITE: The page can be read and written.</li>
     * </ul>
     */
    enum class PageProtection {
        NONE  = 0x0,
        READ  = 0x1,
        WRITE = 0x2
    };


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Calls
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    /**
     * @brief Gets the size of a virtual page in bytes.
     * @return Page size.
     */
    size_t memory_get_page_size();


    /**
     * If v_addr is zero then the location of the memory region will be chosen by the kernel. When v_addr is >0 then the
     * kernel will use the value as a hint to where the memory region should be mapped. v_addr will always be page
     * aligned if needed.
     *
     * <p>
     *  The memory region will always be zero initialized.
     * </p>
     *
     * @brief Map the requested amount of memory into the active applications virtual address space.
     * @param v_addr          Requested start address of the memory region that will be mapped. If zero the kernel
     *                          chooses where to map the memory region.
     * @param num_pages       Number of pages that should be mapped.
     * @param page_protection Requested page protection level.
     * @return Success:                         A pointer to the start of the mapped memory region.
     *          MEM_MAP_BAD_ADDRESS:            The requested memory region intersects kernel memory.
     *          MEM_MAP_BAD_PAGE_PROTECTION:    Unknown page protection flags where given.
     *          MEM_MAP_BAD_MAP:                The mapping of the memory region failed.
     */
    void* memory_allocate_page(void* v_addr, size_t num_pages, PageProtection page_protection);


    /**
     * If v_addr is not page aligned it will be aligned to a page boundary.
     *
     * @brief Remove the requested memory region from the active applications virtual address space.
     * @param v_addr       Staring address of the memory region that will be freed.
     * @param num_pages    Number of pages that should be freed.
     * @return 0: The memory region is freed.
     *          -1: The requested memory region intersects kernel memory.
     *          -2: The free of the memory region failed.
     */
    int memory_free_page(void* v_addr, size_t num_pages);
}

#endif //RUNETOOLCHAIN_MEMORY_H
