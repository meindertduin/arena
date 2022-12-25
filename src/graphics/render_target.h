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

        uint32_t get_screen_texture() const { return texture_color_buffer; }
    private:
        VertexBuffer screen_vertex_buffer { 4 * sizeof(float) };
        ArrayBuffer screen_array_buffer;
        std::shared_ptr<Shader> m_shader;

        uint32_t framebuffer;

        uint32_t texture_color_buffer;
        uint32_t texture_color_buffer_multi_sampled;
        uint32_t render_buffer_object;

        uint32_t intermediate_fbo;
    };
}

