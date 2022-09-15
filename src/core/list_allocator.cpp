#include "list_allocator.h"

#include "../logging.h"

namespace core {
    ListAllocator::ListAllocator(std::size_t total_size, PlacementPolicy policy)
        : Allocator(total_size), policy{policy}
    {
        start_pointer = malloc(total_size);
        this->reset();
    }

    ListAllocator::~ListAllocator() {
        free(start_pointer);
    }

    void* ListAllocator::allocate(std::size_t size, std::size_t alignment) {
        std::size_t padding;
        int block_index {0};
        auto next_block = find(size, alignment, padding, block_index);

        if (next_block == nullptr) {
            THROW_ERROR("ListAllocator exceeded memory of %s bytes", std::to_string(total_size));
        }

        std::size_t alignment_padding = padding - sizeof(AllocatedBlockHeader);
        std::size_t required_size = size + padding;

        std::size_t rest = next_block->size - required_size;
        if (rest > 0) {
            auto new_block = (FreeBlockHeader*) next_block + required_size;
            new_block->size = rest;
            free_blocks.insert(free_blocks.begin() + 1, new_block);
            free_blocks.insert(free_blocks.begin() + block_index + 1, new_block);
        }

        free_blocks.remove(next_block);

        // setup the data block
        std::size_t header_address = (std::size_t) next_block + alignment_padding;
        std::size_t data_address = header_address + sizeof(AllocatedBlockHeader);

        ((AllocatedBlockHeader*) header_address)->size = required_size;
        ((AllocatedBlockHeader*) header_address)->padding = static_cast<uint8_t>(padding);

        used += required_size;
        peak = std::max(peak, used);

        return (void*) data_address;
    }

    void ListAllocator::deallocate(void *ptr) {

    }

    ListAllocator::FreeBlockHeader* ListAllocator::find(std::size_t size, std::size_t alignment, std::size_t &padding, int &pos) const {
        padding = calculate_padding(size, alignment, sizeof(AllocatedBlockHeader));
        for (const auto header : free_blocks) {
            if (header->size >= size + padding) {
                return header;
            }

            pos++;
        }

        return nullptr;
    }

    void ListAllocator::reset() {
        used = 0;
        peak = 0;
        auto first_block = (FreeBlockHeader*) start_pointer;
        first_block->size = total_size;
        free_blocks.push_back(first_block);
    }
}
