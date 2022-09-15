
#include "stack_allocator.h"

namespace core {
    StackAllocator::StackAllocator(const std::size_t total_size) : Allocator(total_size) {
        start_pointer = malloc(total_size);
        offset = 0;
    }

    StackAllocator::~StackAllocator() {
        free(start_pointer);
        start_pointer = nullptr;
    }

    void *StackAllocator::allocate(std::size_t size, std::size_t alignment) {
        printf("allocating size: %lu\n", size);
        const std::size_t current_address = (std::size_t) start_pointer + offset;
        const std::size_t padding = calculate_padding(size, alignment, sizeof (AllocationHeader));

        if (offset + padding + size > total_size) {
            return nullptr;
        }
        offset += padding;

        const std::size_t next_address = current_address + padding;
        const std::size_t header_address = next_address - sizeof(AllocationHeader);
        AllocationHeader allocation_header { static_cast<char>(padding) };

        auto &header_ptr = *(AllocationHeader*) header_address;
        header_ptr = allocation_header;

        offset += size;

        used = offset;
        peak = std::max(peak, used);

        printf("allocated: offset %lu, padding %lu \n", offset, padding);
        return (void*) next_address;
    }

    void StackAllocator::deallocate(void *ptr) {
        const auto current_address = (std::size_t)ptr;
        const std::size_t header_address = current_address - sizeof(AllocationHeader);
        const AllocationHeader * allocation_header{(AllocationHeader*) header_address};

        offset = current_address - allocation_header->padding - (std::size_t)start_pointer;
        used = offset;

        printf("deallocated: offset %lu, padding: %hhd \n", offset, allocation_header->padding);
    }

    void StackAllocator::reset() {
        offset = 0;
        used = 0;
        peak = 0;
    }
}