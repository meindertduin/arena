#pragma once

#include <stdint.h>
#include <memory>

#include "shader.h"
#include "gpu_buffer.h"
#include "render_target.h"
#include "graphic_options.h"

#include "light.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer();

        void render();
        ShaderProgram shader { "shaders/texture_basic.vs", "shaders/texture_basic.fs" };
    private:
        std::unique_ptr<RenderTarget> render_target;
        SharedDataBuffer ubo_matrices { 0, 2 * sizeof(glm::mat4) };
        SharedDataBuffer ubo_lights { 1, 16 * 2 + (DIR_LIGHT_STD140_SIZE * MAX_DIR_LIGHTS) + (POINT_LIGHT_STD140_SIZE * MAX_POINT_LIGHTS) }; // std140 alignment size: 64 = dirlight, int = 16, 112 = pointLight
    };
}
