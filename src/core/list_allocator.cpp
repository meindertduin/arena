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
        std::list<FreeBlockHeader> list;

        auto current_address = (std::size_t) ptr;
        auto header_address = current_address - sizeof(AllocatedBlockHeader);
        AllocatedBlockHeader* allocation_header { (AllocatedBlockHeader*) header_address };

        Node* free_node = (Node* ) header_address;
        free_node->data.size = allocation_header->size + allocation_header->padding;
        free_node->next = nullptr;

        auto it = free_blocks.head;
        Node* it_prev = nullptr;

        while (it != nullptr) {
            if (ptr < it) {
                free_blocks.insert(free_node, it_prev);
                break;
            }

            it_prev = it;
            it = it->next;
        }

        used -= free_node->data.size;

        coalescene(free_node, it_prev);
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

    void ListAllocator::coalescene(Node* free_node, Node* previous_node) {
        if (free_node->next != nullptr &&
            (std::size_t) free_node + free_node->data.size == (std::size_t) free_node->next)
        {
            free_node.data.size += free_node->next->data.size;
            free_blocks.remove(free_node->next, free_node);
        }

        if (previous_node != nullptr &&
            (std::size_t) previous_node + previous_node->data.size == (std::size_t) free_node)
        {
            previous_node->data.size += free_node->data.size;
            free_blocks.remove(free_node, previous_node);
        }
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
