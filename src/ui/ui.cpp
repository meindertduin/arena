#include "ui.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    UI::UI() {
        root = std::make_unique<ButtonComponent>(glm::ivec2{ 100, 100 }, glm::ivec2{ 130, 40 });
    }

    static bool on_click(UIComponent *component, const UIMouseClickEvent &event) {
        auto &component_ref = *component;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            component_ref.handle_click(event);
            return true;
        }

        for (auto &child : component_ref.children) {
            if (on_click(&child, event))
                return true;
        }

        return false;
    }

    void UI::handle_mouse_button_event(const input::KeyCombination &combi) {
        if (combi.action == input::KEY_PRESS) {
            auto mouse_pos = input::get_mouse_position();
            on_click(root.get(), UIMouseClickEvent{ .button = combi.key, .mouse_pos = mouse_pos });
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
