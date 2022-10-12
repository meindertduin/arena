#pragma once

#include <memory>

#include "render_target.h"
#include "../ui/component.h"

namespace graphics {
    struct UiRenderContext {
        UiRenderContext(const glm::ivec2 &pos) : incremental_pos{pos} { }
        UiRenderContext(const glm::ivec2 &pos, ui::UiElement *sibling) : incremental_pos{pos}, sibling{sibling} { }
        glm::vec2 incremental_pos;
        ui::UiElement *sibling { nullptr };
    };

    class UIRenderer {
    public:
        explicit UIRenderer(std::shared_ptr<RenderTarget> render_target);
        void before_ui_rendering();
        void after_ui_rendering();
        void render(ui::UiElement *element, UiRenderContext context = UiRenderContext{ glm::ivec2 { 0, 0 }});
    private:
        std::shared_ptr<RenderTarget> render_target;
        ShaderProgram shader { "shaders/ui.vert", "shaders/ui.frag" };

        graphics::GpuPlane plane;

        static glm::ivec2 convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size);
        void render_geometry(ui::GeometryAttribute *attribute, const glm::ivec2 &pos, ui::UiElement *element);
        void render_plane(glm::vec4 &color, const glm::ivec2 &pos, const glm::ivec2 &size);
    };
}
