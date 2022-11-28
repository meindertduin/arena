#pragma once

#include <memory>

#include "render_target.h"
#include "rect.h"
#include "color.h"
#include "geometry.h"

namespace graphics {
    class UIRenderer {
    public:
        explicit UIRenderer(std::shared_ptr<RenderTarget> render_target);
        void before_ui_rendering();
        void after_ui_rendering();

        void draw_rect(const IRect &rect, const Color &color);
    private:
        std::shared_ptr<RenderTarget> render_target;
        ShaderProgram m_shader { "shaders/ui" };

        graphics::GpuPlane plane;

        static glm::ivec2 convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size);
        void render_plane(glm::vec4 &color, const glm::ivec2 &pos, const glm::ivec2 &size);
    };
}
