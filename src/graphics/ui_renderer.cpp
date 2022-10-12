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
        if (!element->display) {
            return;
        }

        shader.use();

        glm::ivec2 pos = convert_to_gl_pos(element->pos, element->size);

        // render the geometry
        auto hovered_geometry_attribute = element->get_attribute_opt<ui::GeometryAttribute>(ui::AttributeType::GeometryHovered);
        if (element->is_hovered && hovered_geometry_attribute.has_value()) {
            auto attribute = hovered_geometry_attribute.value();
            render_geometry(attribute, pos, element);
        } else {
            auto geometry_attribute = element->get_attribute_opt<ui::GeometryAttribute>(ui::AttributeType::Geometry);
            if (geometry_attribute.has_value()) {
                render_geometry(geometry_attribute.value(), pos, element);
            }
        }

        // render the text
        auto text_attribute = element->get_attribute_opt<ui::TextAttribute>(ui::AttributeType::Text);
        if (text_attribute.has_value()) {
            if (text_attribute.value()->center_text) {
                // Also center the text on the x-axis
                auto text_size = text_attribute.value()->text_size;
                auto text_length = text_attribute.value()->text.length();
                auto text_width = text_size * text_length / 1.95f;

                int text_pos_x = text_width >= element->size.x ? pos.x : pos.x + (element->size.x - text_width) / 2;
                int text_pos_y = text_size >= element->size.y ? pos.y : pos.y + (element->size.y - text_size) / 1.5f;

                glm::ivec2 text_pos = { text_pos_x, text_pos_y };
                global.text_renderer->render(text_attribute.value()->text, text_pos, text_attribute.value()->text_size);
            } else {
                global.text_renderer->render(text_attribute.value()->text, pos, text_attribute.value()->text_size);
            }
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


    void UIRenderer::render_geometry(ui::GeometryAttribute *attribute, const glm::ivec2 &pos, ui::UiElement *element) {
        if (attribute->border_size > 0) {
            auto border_pos = pos - attribute->border_size;
            auto border_plane_size = element->size + attribute->border_size * 2;
            render_plane(attribute->border_color, border_pos, border_plane_size);
        }
        render_plane(attribute->background_color, pos, element->size);
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
}
