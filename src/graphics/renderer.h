#pragma once

#include <stdint.h>

namespace graphics {
    struct Renderer {
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void render();
    };
}
