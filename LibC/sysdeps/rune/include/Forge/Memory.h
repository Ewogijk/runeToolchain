#ifndef FORGE_MEMORY_H
#define FORGE_MEMORY_H


#include <Ember/MemoryBits.h>

namespace Forge {

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
	 * @brief Allocate the requested amount of memory in the active applications virtual address space.
	 * @param v_addr          Requested start address of the memory region that will be allocated. If zero the kernel
	 *                          chooses where to map the memory region.
	 * @param num_pages       Number of pages that should be mapped.
	 * @param page_protection Requested page protection level.
	 * @return Success:  A pointer to the start of the mapped memory region.<br>
	 *          BAD_ARG: The requested memory region intersects kernel memory or the page protection
	 *                   flag is invalid.<br>
	 *          FAULT:   The memory allocation failed.
	 */
    void* memory_allocate_page(void* v_addr, size_t num_pages, Ember::PageProtection page_protection);


	/**
	 * If v_addr is not page aligned it will be aligned to a page boundary.
	 *
	 * @brief Remove the requested memory region from the active applications virtual address space.
	 * @param v_addr       Staring address of the memory region that will be freed.
	 * @param num_pages    Number of pages that should be freed.
	 * @return OKAY:     The memory region is freed.<br>
	 *          BAD_ARG: The requested memory region intersects kernel memory.<br>
	 *          FAULT:   The memory free failed.
	 */
    int memory_free_page(void* v_addr, size_t num_pages);
}

#endif //FORGE_MEMORY_H
