#include <Forge/Memory.h>

#include <Forge/SystemCall.h>


namespace Forge {
	// Cache the page size to minimize system calls
	size_t page_size = 0;

    size_t memory_get_page_size() {
    	if (page_size == 0)
    		page_size = static_cast<size_t>(system_call0(MEMORY_GET_PAGE_SIZE));
        return page_size;
    }


    void* memory_allocate_page(void* v_addr, size_t num_pages, PageProtection page_protection) {
        return (void*) (uintptr_t) system_call3(
                MEMORY_ALLOCATE_PAGE,
                (U64) (uintptr_t) v_addr,
                num_pages,
                (U64) page_protection
        );
    }


    int memory_free_page(void* v_addr, size_t num_pages) {
        return system_call2(MEMORY_FREE_PAGE, (U64) (uintptr_t) v_addr, num_pages);
    }
}
