#pragma once

#include "gpu_buffer.h"
#include "shader.h"
#include "graphic_options.h"

namespace graphics {
    struct RenderTarget {
    public:
        RenderTarget();
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
        VertexBuffer screen_vertex_buffer { 4 * sizeof(float) };
        ArrayBuffer screen_array_buffer;
        ShaderProgram screen_shader { "shaders/screen.vert", "shaders/screen.frag" };

        uint32_t framebuffer;
        uint32_t texture_color_buffer;
        uint32_t texture_color_buffer_multi_sampled;
        uint32_t render_buffer_object;

        uint32_t intermediate_fbo;
    };
}

