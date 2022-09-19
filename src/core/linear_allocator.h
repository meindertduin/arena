#pragma once

#include "allocator.h"

#include <vector>

namespace core {
    class LinearAllocator : public Allocator {
    public:
        explicit LinearAllocator(std::size_t total_size);
        explicit LinearAllocator(std::size_t total_size, void* start_ptr);
        virtual ~LinearAllocator();

        void* allocate(std::size_t size, std::size_t alignment) override;
        void deallocate(void *ptr) override;
        void reset();
    protected:
        std::size_t offset;
    };

    // This class is a wrapper to use the linear allocator in std library container types like the vector
    // Too bad this class cannot be a specialization for StdListAllocator, because std::allocator<T> allows only one template type.
    template<typename T>
    class StdLinearAllocator : public std::allocator<T> {
    public:
        LinearAllocator *allocator = nullptr;
        std::size_t alignment;

        constexpr T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(this->allocator->allocate(n * sizeof(T), alignment));
        }

        constexpr void deallocate(T* p, std::size_t n) {
            printf("deallocating from std::allocator\n");
            // linear doesnt deallocate
        }

        explicit StdLinearAllocator(LinearAllocator *allocator, std::size_t alignment = DefaultAlignment)
            : allocator(allocator) , alignment(alignment) { }

        StdLinearAllocator(const StdLinearAllocator &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
            alignment = other.alignment;
        }

        template <class U>
        StdLinearAllocator(const StdLinearAllocator<U> &other) noexcept: std::allocator<T>(other) {
            allocator = other.allocator;
            alignment = other.alignment;
        }

        ~StdLinearAllocator() noexcept {
            allocator->reset();
        }
    };

    template<typename T>
    using LinearAllocVector = std::vector<T, StdLinearAllocator<T>>;
}
