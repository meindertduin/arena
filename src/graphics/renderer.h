#pragma once

#include <stdint.h>
#include "shader.h"
#include "gpu_buffer.h"
#include "render_target.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void render();
        ShaderProgram shader { "shaders/basic.vs", "shaders/basic.fs" };
    private:
        uint32_t width, height;
        RenderTarget* render_target;
    };
}
