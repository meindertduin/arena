#pragma once

#include "allocator.h"

namespace core {
    class StackAllocator : public Allocator {
    public:
        StackAllocator(std::size_t total_size);

        virtual ~StackAllocator();

        void* allocate(std::size_t size, std::size_t alignment) override;
        void deallocate(void *ptr) override;

        virtual void reset();
    protected:
        void* start_ptr = nullptr;
        std::size_t offset;
    private:
        StackAllocator(StackAllocator &allocator);

        struct AllocationHeader {
            char padding;
        };
    };

}

