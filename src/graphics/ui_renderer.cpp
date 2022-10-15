#include "ui_renderer.h"

#include "renderer.h"
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

    glm::ivec2 UIRenderer::convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size) {
        return {
                pos.x,
                global.graphic_options->screen_dimensions.y - pos.y - size.y,
        };
    }

    void UIRenderer::render_plane(glm::vec4 &color, const glm::ivec2 &pos, const glm::ivec2 &size) {
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);

        shader.set_property("color", color);

        if (size.x > 0 && size.y > 0 && color.w > 0.0f) {
            plane.set_pos_and_size(pos, size);
            plane.render();
        }
    }

    void UIRenderer::draw_rect(const IRect &rect, const Color &color) {
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);

        shader.set_property("color", color.color());

        if (rect.size().width() > 0 && rect.size().height() > 0 && color.alpha() > 0.0f) {
            plane.set_from_rect(rect);
            plane.render();
        }
    }
}
