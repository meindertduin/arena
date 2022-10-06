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
        void render(ui::UiElement *element);
    private:
        std::shared_ptr<RenderTarget> render_target;
        ShaderProgram shader { "shaders/ui.vert", "shaders/ui.frag" };

        graphics::GpuPlane plane;

        static glm::ivec2 convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size);
        void render_geometry(ui::GeometryAttribute *geometry, const glm::ivec2 &pos, const glm::ivec2 &size);
    };
}
