#include "list_allocator.h"

namespace core {
    ListAllocator::ListAllocator(std::size_t total_size, PlacementPolicy policy)
        : Allocator(total_size), policy{policy}
    {
        start_pointer = malloc(total_size);
    }

    ListAllocator::~ListAllocator() {
        free(start_pointer);
    }

    void* ListAllocator::allocate(std::size_t size, std::size_t alignment) {
        std::size_t allocation_block_size = sizeof(AllocatedBlockHeader);
        std::size_t free_block_header_size = sizeof(FreeBlockHeader);
    }
}
