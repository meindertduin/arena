#pragma once

#include "allocator.h"

namespace core {
    class LinearAllocator : public Allocator {
    public:
        explicit LinearAllocator(std::size_t total_size);
        virtual ~LinearAllocator();

        void init() override;
        void* allocate(std::size_t size, std::size_t alignment) override;
        void deallocate(void *ptr) override;
        void reset();
    protected:
        void* start_pointer;
        std::size_t offset;
    private:
        static std::size_t calculate_padding(std::size_t base_address, std::size_t alignment);
    };
}
