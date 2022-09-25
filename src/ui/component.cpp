#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    ButtonComponent::ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
        border.set_size_and_position({ pos.x, pos.y}, { size.x, size.y });
        background.set_size_and_position({ pos.x + 2, pos.y + 2 }, { size.x - 4, size.y - 4 });
    }

    void ButtonComponent::render() {
        global.ui_renderer->render(border, { 1.0f, 1.0f, 1.0f, 1.0f });
        global.ui_renderer->render(background, { 1.0f, 0, 0, 1.0f });
        global.text_renderer->render("Click me!", { pos.x + 10, pos.y + 10 });
    }

    void ButtonComponent::handle_click(const UIMouseClickEvent &event) {
        printf("Element is clicked!\n");
    }
}