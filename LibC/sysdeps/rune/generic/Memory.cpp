#include <rune/Memory.h>

#include <rune/SystemCall.h>


namespace Rune {
    size_t memory_get_page_size() {
        return (size_t) system_call0(MEMORY_GET_PAGE_SIZE);
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
