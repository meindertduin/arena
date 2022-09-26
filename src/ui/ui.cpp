#include "ui.h"
#include "../global.h"
#include "../graphics/renderer.h"
#include "component_builder.h"

namespace ui {
    UI::UI() {
        ComponentBuilder<RootComponent> builder;
        root = builder
                .with_pos_and_size(glm::ivec2 { 0, 0 }, glm::ivec2 { global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y })
                .with_child<ButtonComponent>([](ComponentBuilder<ButtonComponent> &builder) {
                    builder.with_rel_pos_and_size(glm::ivec2{ 10, 10 }, glm::ivec2{ 130, 40 });
                })
                .build();
    }

    void UI::handle_mouse_move_event() {
        auto mouse_pos = input::get_mouse_position();
        on_mouse_move(root.get(), UIMouseMoveEvent{ .mouse_pos = mouse_pos });
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

    void UI::render() {
        global.ui_renderer->before_ui_rendering();
        root->render();
        global.ui_renderer->after_ui_rendering();
    }

    bool UI::on_mouse_move(UIComponent *component, const UIMouseMoveEvent &event) {
        auto &component_ref = *component;

        component_ref.is_hovered = false;
        bool hovers_element;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            component_ref.is_hovered = true;
            hovers_element = true;
        }

        if (!hovers_element) {
            return false;
        }

        for (auto &child : component_ref.children) {
            on_mouse_move(child.get(), event);
        }

        return true;
    }

    bool UI::on_click(UIComponent *component, const UIMouseClickEvent &event) const {
        auto &component_ref = *component;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            component_ref.handle_click(event);
        }

        for (auto &child : component_ref.children) {
            on_click(child.get(), event);
        }

        return false;
    }
}
