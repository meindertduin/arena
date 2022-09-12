#pragma once

#include <cstddef>

namespace core {
    class Allocator {
    public:
        explicit Allocator(const std::size_t total_size) : total_size{total_size}, used{0}, peak{0} { }
        virtual void init() = 0;
        virtual void* allocate_mem(std::size_t size, std::size_t alignment = 0) = 0;
        virtual void free_mem(void *ptr) = 0;
    protected:
        std::size_t total_size;
        std::size_t used;
        std::size_t peak;
    };
}