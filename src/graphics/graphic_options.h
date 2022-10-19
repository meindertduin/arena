#pragma once

#include <glm/glm.hpp>
#include "../core/event_dispatcher.h"
#include "rect.h"

namespace graphics {
    class GraphicOptions {
    public:
        bool antialiasing;

        GraphicOptions() = default;
        GraphicOptions(bool antialiasing, const U32Size &size) :
            antialiasing(antialiasing), m_size{size} {}

        [[nodiscard]] constexpr ALWAYS_INLINE U32Size size() const { return m_size; }
        void set_size(const U32Size &size);
        void set_antialiasing(bool new_value);
    private:
        U32Size m_size;
    };
}
