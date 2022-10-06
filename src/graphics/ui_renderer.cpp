#include "ui_renderer.h"

#include "../global.h"

namespace graphics {
    UIRenderer::UIRenderer(std::shared_ptr<RenderTarget> render_target) : render_target{std::move( render_target )} {
        shader.link();
    }

    void UIRenderer::before_ui_rendering() {
        render_target->disable_depth_test();
    }

    void UIRenderer::after_ui_rendering() {
        render_target->enable_depth_test();
    }

    void UIRenderer::render(ui::UiElement *root) {
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);
        shader.set_property("color", root->background_color);

        glm::ivec2 pos = {
                root->pos.x,
                global.graphic_options->screen_dimensions.y - root->pos.y - root->size.y,
        };

        plane.set_pos_and_size(pos, root->size);
        plane.render();
    }
}
