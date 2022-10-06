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

    void UIRenderer::render(ui::UiElement *element) {
        shader.use();
        glm::mat4 projection = glm::ortho(0.0f, (float)global.graphic_options->screen_dimensions.x,
                                          0.0f, (float)global.graphic_options->screen_dimensions.y);

        shader.set_property("projection", projection);
        shader.set_property("color", element->background_color);

        glm::ivec2 pos = convert_to_gl_pos(element->pos, element->size);

        if (element->size.x > 0 && element->size.y > 0 && element->background_color.w > 0.0f) {
            plane.set_pos_and_size(pos, element->size);
            plane.render();
        }

        if (element->attributes.contains(ui::AttributeType::Text)) {
            auto attribute = reinterpret_cast<ui::TextAttribute*>(element->attributes[ui::AttributeType::Text].get());
            global.text_renderer->render(attribute->text, pos, attribute->text_size);
        }

        // TODO This goes to the deepest level first, that could be problematic
        for (auto &child_element : element->children)
            render(child_element.get());
    }

    glm::ivec2 UIRenderer::convert_to_gl_pos(const glm::ivec2 pos, const glm::ivec2 size) {
        return {
                pos.x,
                global.graphic_options->screen_dimensions.y - pos.y - size.y,
        };
    }
}
