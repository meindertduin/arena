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
        Node* found_node, *previous;
        find(size, alignment, padding, found_node, previous);

        if (found_node == nullptr) {
            THROW_ERROR("ListAllocator exceeded memory of %s bytes", std::to_string(total_size));
        }

        std::size_t alignment_padding = padding - sizeof(AllocatedBlockHeader);
        std::size_t required_size = size + padding;

        std::size_t rest = found_node->data.size - required_size;

        if (rest > 0) {
            auto new_free_node = (Node*)((std::size_t) found_node + required_size);
            new_free_node->data.size = rest;
            free_blocks.insert(new_free_node, found_node);
        }

        free_blocks.remove(found_node, previous);

        // setup the data block
        std::size_t header_address = (std::size_t) found_node + alignment_padding;
        std::size_t data_address = header_address + sizeof(AllocatedBlockHeader);

        ((AllocatedBlockHeader*) header_address)->size = required_size;
        ((AllocatedBlockHeader*) header_address)->padding = static_cast<uint8_t>(padding);

        used += required_size;
        peak = std::max(peak, used);

        return (void*) data_address;
    }

    void ListAllocator::deallocate(void *ptr) {

    }

    void ListAllocator::find(std::size_t size, std::size_t alignment, std::size_t &padding, Node* &found_node, Node* &previous) const {
        padding = calculate_padding(size, alignment, sizeof(AllocatedBlockHeader));

        auto it = free_blocks.head;
        Node* it_previous = nullptr;

        while (it != nullptr) {
            if (it->data.size >= size + padding) {
                break;
            }
            it_previous = it;
            it = it->next;
        }

        found_node = it;
        previous = it_previous;
    }

    void ListAllocator::reset() {
        used = 0;
        peak = 0;
        auto first_node = (Node*) start_pointer;
        first_node->data.size = total_size;
        first_node->next = nullptr;
        free_blocks.head = nullptr;
        free_blocks.insert(first_node, nullptr);
    }
}
