#pragma once

#include <stdint.h>
#include "shader.h"
#include "gpu_buffer.h"

namespace graphics {
    struct Renderer {
    public:
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void render();
        ShaderProgram shader { "shaders/basic.vs", "shaders/basic.fs" };
    private:
        uint32_t width, height;
        VertexBuffer screen_vertex_buffer { 4 * sizeof(float) };
        ArrayBuffer screen_array_buffer;
        ShaderProgram screen_shader { "shaders/screen.vs", "shaders/screen.fs" };
    };
}
