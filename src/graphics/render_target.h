#pragma once

#include "gpu_buffer.h"
#include "shader.h"
#include "graphic_options.h"

namespace graphics {
    class RenderTarget {
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

        void enable_depth_test();
        void disable_depth_test();
    private:
        VertexBuffer screen_vertex_buffer { 4 * sizeof(float) };
        ArrayBuffer screen_array_buffer;
        ShaderProgram m_shader { "shaders/screen" };

        uint32_t framebuffer;
        uint32_t texture_color_buffer;
        uint32_t texture_color_buffer_multi_sampled;
        uint32_t render_buffer_object;

        uint32_t intermediate_fbo;
    };
}

