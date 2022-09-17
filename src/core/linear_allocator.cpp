
#include <cstdlib>
#include <algorithm>
#include "linear_allocator.h"

namespace core {
    LinearAllocator::LinearAllocator(const std::size_t total_size)
        : Allocator(total_size) ,offset{0}
    {
        start_pointer = malloc(total_size);
        offset = 0;
    }

    LinearAllocator::LinearAllocator(std::size_t total_size, void* start_ptr) : Allocator(total_size, start_ptr) {
        offset = 0;
    }

    LinearAllocator::~LinearAllocator() {
        if (free_on_destruct) {
            free(start_pointer);
        }
        start_pointer = nullptr;
    }

    void* LinearAllocator::allocate(std::size_t size, std::size_t alignment) {
        std::size_t padding = 0;
        std::size_t current_address = (std::size_t)start_pointer + offset;

        if (alignment != 0 && offset % alignment != 0) {
            padding = calculate_padding(size, alignment);
        }

        if (offset + padding + size > total_size) {
            return nullptr;
        }

        offset += padding;
        const std::size_t next_address = current_address + padding;
        offset += size;

        used = offset;
        peak = std::max(peak, used);

        return (void*) next_address;
    }

    void LinearAllocator::deallocate(void *ptr) {
        // linear allocator doesn't deallocate
    }

    void LinearAllocator::reset() {
        offset = 0;
        used = 0;
        peak = 0;
    }
}