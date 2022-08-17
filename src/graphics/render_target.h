#pragma once

#include "gpu_buffer.h"
#include "shader.h"

namespace graphics {
    struct RenderTarget {
    public:
        RenderTarget(uint32_t width, uint32_t height);
        ~RenderTarget();

        RenderTarget(const RenderTarget&) = delete;
        RenderTarget(RenderTarget&&) = delete;

        RenderTarget& operator=(const RenderTarget&) = delete;
        RenderTarget& operator=(RenderTarget&&) = delete;

        void bind();
        void unbind();
        void clear();
        void render();
    private:
        uint32_t width, height;

        VertexBuffer screen_vertex_buffer { 4 * sizeof(float) };
        ArrayBuffer screen_array_buffer;
        ShaderProgram screen_shader { "shaders/screen.vs", "shaders/screen.fs" };

        uint32_t framebuffer;
        uint32_t texture_color_buffer;
        uint32_t render_buffer_object;
    };
}
