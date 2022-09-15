#pragma once

#include "allocator.h"
#include "double_linked_list.h"

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
    protected:

    private:
        PlacementPolicy policy;

        struct FreeBlockHeader {
            std::size_t size;
        };
        struct AllocatedBlockHeader {
            std::size_t size;
            uint8_t padding;
        };

        std::list<FreeBlockHeader*> free_blocks;
        FreeBlockHeader* find(std::size_t size, std::size_t alignment, std::size_t &padding, int &pos) const;
    };
}