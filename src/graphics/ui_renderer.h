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
        void render(ui::UiElement *root);
    private:
        std::shared_ptr<RenderTarget> render_target;
        ShaderProgram shader { "shaders/ui.vert", "shaders/ui.frag" };

        graphics::GpuPlane plane;
    };
}
