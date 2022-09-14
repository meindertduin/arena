
#include "stack_allocator.h"

namespace core {
    StackAllocator::StackAllocator(const std::size_t total_size) : Allocator(total_size) {
        start_ptr = malloc(total_size);
        offset = 0;
    }

    StackAllocator::~StackAllocator() {
        free(start_ptr);
        start_ptr = nullptr;
    }

    void *StackAllocator::allocate(std::size_t size, std::size_t alignment) {
        const std::size_t current_address = (std::size_t) start_ptr + offset;
        const std::size_t padding = calculate_padding(current_address, alignment, sizeof (AllocationHeader));

        if (offset + padding + size > total_size) {
            return nullptr;
        }
        offset += padding;

        const std::size_t next_address = current_address + padding;
        const std::size_t header_address = next_address - sizeof(AllocationHeader);
        AllocationHeader allocation_header { static_cast<char>(padding) };
        auto *header_ptr = (AllocationHeader*) header_address;
        header_ptr = &allocation_header;

        offset += size;

        used = offset;
        peak = std::max(peak, used);

        return (void*) next_address;
    }

    void StackAllocator::deallocate(void *ptr) {
        const auto current_address = (std::size_t) ptr;
        const std::size_t header_address = current_address - sizeof(AllocationHeader);
        const AllocationHeader * allocation_header{(AllocationHeader *) header_address};

        offset = current_address - allocation_header->padding - (std::size_t)start_ptr;
        used = offset;
    }

    void StackAllocator::reset() {
        offset = 0;
        used = 0;
        peak = 0;
    }
}