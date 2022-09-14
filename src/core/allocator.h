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

    constexpr std::size_t calculate_padding(std::size_t base_address, std::size_t alignment) {
        const std::size_t multiplier = (base_address / alignment) + 1;
        const std::size_t aligned_address = multiplier * alignment;
        const std::size_t padding = aligned_address - base_address;

        return padding;
    }

    constexpr std::size_t calculate_padding(std::size_t base_address, std::size_t alignment, std::size_t header_size) {
        auto padding = calculate_padding(base_address, alignment);
        auto needed_space = header_size;

        if (padding < needed_space) {
            needed_space -= padding;

            // How many alignments I need to fit the header
            if(needed_space % alignment > 0){
                padding += alignment * (1+(needed_space / alignment));
            }else {
                padding += alignment * (needed_space / alignment);
            }
        }

        return padding;
    }
}