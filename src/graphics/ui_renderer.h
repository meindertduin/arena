#pragma once

#include <memory>

#include "render_target.h"
#include "../ui/component.h"

namespace graphics {
    class UIRenderer {
    public:
        explicit UIRenderer(std::shared_ptr<RenderTarget> render_target);
        void before_ui_rendering();
        void after_ui_rendering();
        void render(ui::UiElement *element, glm::ivec2 pos = glm::ivec2{ 0, 0 });
    private:
        std::shared_ptr<RenderTarget> render_target;
        ShaderProgram shader { "shaders/ui.vert", "shaders/ui.frag" };

        graphics::GpuPlane plane;

        static glm::ivec2 convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size);
        void render_geometry(ui::GeometryAttribute *attribute, const glm::ivec2 &pos, ui::UiElement *element);
        void render_plane(glm::vec4 &color, const glm::ivec2 &pos, const glm::ivec2 &size);
    };
}
