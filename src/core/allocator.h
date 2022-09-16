#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace core {
    constexpr std::size_t DefaultAlignment = 8;

    class Allocator {
    public:
        explicit Allocator(const std::size_t total_size) : total_size{total_size}, used{0}, peak{0}, start_pointer{nullptr} { }
        virtual void* allocate(std::size_t size, std::size_t alignment) = 0;
        virtual void deallocate(void *ptr) = 0;
    protected:
        std::size_t total_size;
        void* start_pointer;
        std::size_t used;
        std::size_t peak;
    };

    inline constexpr std::size_t calculate_padding(std::size_t size, std::size_t alignment) {
        auto remainder = size % alignment;
        if (remainder > 0) {
            return alignment - remainder;
        }

        return 0;
    }

    inline constexpr std::size_t calculate_padding(std::size_t size, std::size_t alignment, std::size_t header_size) {
        if (alignment == 0)
            return header_size;

        auto padding = calculate_padding(size, alignment);
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