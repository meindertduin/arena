#pragma once

#include <stdint.h>
#include <memory>

#include "shader.h"
#include "gpu_buffer.h"
#include "render_target.h"
#include "graphic_options.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer(uint32_t width, uint32_t height);

        void render();
        ShaderProgram shader { "shaders/texture_basic.vs", "shaders/texture_basic.fs" };
    private:
        GraphicOptions options;
        std::unique_ptr<RenderTarget> render_target;
    };
}
