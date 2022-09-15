#pragma once

#include "allocator.h"
#include "singly_linked_list.h"

#include <list>

namespace core {
    class ListAllocator : Allocator {
    public:
        enum class PlacementPolicy {
            First,
            Best,
        };

        ListAllocator(std::size_t total_size, PlacementPolicy policy);
        virtual ~ListAllocator();

        void* allocate(std::size_t size, std::size_t alignment) override;
        void deallocate(void *ptr) override;
        void reset();
    private:
        PlacementPolicy policy;

        struct FreeBlockHeader {
            std::size_t size;
        };
        struct AllocatedBlockHeader {
            std::size_t size;
            uint8_t padding;
        };

        using Node = SinglyLinkedList<FreeBlockHeader>::Node;
        SinglyLinkedList<FreeBlockHeader> free_blocks;

        void find(std::size_t size, std::size_t alignment, std::size_t &padding, Node* &found_node, Node* &previous) const;

        void coalescene(Node* free_node, Node* previous_node);
    };
}