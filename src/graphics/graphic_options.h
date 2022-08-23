#pragma once

#include <glm/glm.hpp>

namespace graphics {
    struct GraphicOptions {
        bool antialiasing;
        glm::u32vec2 screen_dimensions;
    };
}
