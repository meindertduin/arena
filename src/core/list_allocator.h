#pragma once

#include "allocator.h"

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

        virtual void reset();
    protected:

    private:
        struct FreeBlockHeader {
            std::size_t size;
        };
        struct AllocatedBlockHeader {
            std::size_t size;
            char padding;
        };
    };
}