#include "ui.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    UI::UI() {
        auto node = new UINode{};
        node->component = std::make_unique<ButtonComponent>(glm::ivec2{ 100, 100 }, glm::ivec2{ 130, 40 });
        root = std::unique_ptr<UINode>(node);
    }

    void UI::handle_mouse_button_event(const input::KeyCombination &combi) {
        if (combi.key == input::MOUSE_1) {
            auto mouse_pos = input::get_mouse_position();
            root->on_click(UIMouseClickEvent{ .button = combi.key, .mouse_pos = mouse_pos });
        }
    }

    void UI::handle_key_event(const input::KeyCombination &combi) {
        // TODO implement
    }

    void UI::render() const {
        global.ui_renderer->before_ui_rendering();
        root->render();
        global.ui_renderer->after_ui_rendering();
    }
}
