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

    template<typename T>
    class StdLinearAllocator : public std::allocator<T> {
    public:
        LinearAllocator *allocator = nullptr;

        constexpr T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(this->allocator->allocate(n, 0));
        }

        constexpr void deallocate(T* p, std::size_t n) {
            this->allocator->deallocate(p);
        }

        StdLinearAllocator() = delete;
        explicit StdLinearAllocator(LinearAllocator *allocator) : allocator(allocator) { }

        StdLinearAllocator(const StdLinearAllocator &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        template <class U>
        StdLinearAllocator(const StdAllocator<U> &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        ~StdLinearAllocator() noexcept {
            allocator->reset();
            allocator = nullptr;
        }
    };
}
