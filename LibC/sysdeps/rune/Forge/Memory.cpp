#include <Forge/Memory.h>

#include <Ember/SystemCallID.h>

#include <Forge/SystemCall.h>


namespace Forge {
	// Cache the page size to minimize system calls
	size_t page_size = 0;

    size_t memory_get_page_size() {
    	if (page_size == 0)
    		page_size = static_cast<size_t>(system_call0(Ember::Memory::GET_PAGE_SIZE));
        return page_size;
    }


    void* memory_allocate_page(void* v_addr, const size_t num_pages, const Ember::PageProtection page_protection) {
        return reinterpret_cast<void*>(system_call3(
	        Ember::Memory::ALLOCATE_PAGE,
	        reinterpret_cast<uintptr_t>(v_addr),
	        num_pages,
	        page_protection
        ));
    }


    int memory_free_page(void* v_addr, const size_t num_pages) {
        return system_call2(Ember::Memory::FREE_PAGE, (U64) reinterpret_cast<uintptr_t>(v_addr), num_pages);
    }
}
