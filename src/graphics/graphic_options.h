#pragma once

#include <glm/glm.hpp>
#include "../core/event_dispatcher.h"

namespace graphics {
    struct GraphicOptions {
    public:
        bool antialiasing;
        glm::u32vec2 screen_dimensions;

        GraphicOptions() = default;
        GraphicOptions(bool antialiasing, glm::u32vec2 screen_dimensions) :
            antialiasing(antialiasing), screen_dimensions(screen_dimensions) {}

        void set_antialiasing(bool new_value);
        void set_screen_dimensions(glm::u32vec2 new_value);
    };
}
