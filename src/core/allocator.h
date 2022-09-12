#pragma once

#include <cstddef>
#include <memory>

namespace core {
    class Allocator {
    public:
        explicit Allocator(const std::size_t total_size) : total_size{total_size}, used{0}, peak{0} { }
        virtual void init() = 0;
        virtual void* allocate(std::size_t size, std::size_t alignment = 0) = 0;
        virtual void deallocate(void *ptr) = 0;
    protected:
        std::size_t total_size;
        std::size_t used;
        std::size_t peak;
    };

    template<typename T>
    class StdAllocator : public std::allocator<T> {
    public:
        Allocator *allocator = nullptr;

        constexpr T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(this->allocator->allocate(n));
        }

        constexpr void deallocate(T* p, std::size_t n) {
            this->allocator->deallocate(p);
        }

        StdAllocator() = delete;
        explicit StdAllocator(Allocator *allocator) : allocator(allocator) { }

        StdAllocator(const StdAllocator &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        template <class U>
        StdAllocator(const StdAllocator<U> &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        ~StdAllocator() noexcept {
            allocator = nullptr;
        }
    };
}