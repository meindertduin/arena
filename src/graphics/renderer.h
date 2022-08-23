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
        Renderer();

        void render();
        ShaderProgram shader { "shaders/texture_basic.vs", "shaders/texture_basic.fs" };
    private:
        std::unique_ptr<RenderTarget> render_target;
    };
}
