#pragma once

#include "allocator.h"

#include <vector>

namespace core {
    class LinearAllocator : public Allocator {
    public:
        explicit LinearAllocator(std::size_t total_size);
        virtual ~LinearAllocator();

        void* allocate(std::size_t size, std::size_t alignment) override;
        void deallocate(void *ptr) override;
        void reset();
    protected:
        void* start_pointer;
        std::size_t offset;
    };

    // This class is a wrapper to use the linear allocator in std library container types like the vector
    // Too bad this class cannot be a specialization for StdAllocator, because std::allocator<T> allows only one template type.
    template<typename T>
    class StdLinearAllocator : public std::allocator<T> {
    public:
        LinearAllocator *allocator = nullptr;

        constexpr T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(this->allocator->allocate(n * sizeof(T), 8));
        }

        constexpr void deallocate(T* p, std::size_t n) {
            // linear doesnt deallocate
        }

        StdLinearAllocator() = delete;
        explicit StdLinearAllocator(LinearAllocator *allocator) : allocator(allocator) { }

        StdLinearAllocator(const StdLinearAllocator &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        template <class U>
        StdLinearAllocator(const StdLinearAllocator<U> &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
        }

        ~StdLinearAllocator() noexcept {
            allocator->reset();
        }
    };


    template<typename T>
    using AllocVector = std::vector<T, StdLinearAllocator<T>>;
}
