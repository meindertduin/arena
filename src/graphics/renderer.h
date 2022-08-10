#pragma once

#include <stdint.h>
#include "shader.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void render();
        ShaderProgram shader { "shaders/basic.vs", "shaders/basic.fs" };
    private:
        uint32_t width, height;
    };
}
