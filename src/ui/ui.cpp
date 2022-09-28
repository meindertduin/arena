#include "ui.h"
#include "../global.h"
#include "../graphics/renderer.h"
#include "component_builder.h"

namespace ui {
    UI::UI() {
        ComponentBuilder<RootComponent> builder;
        root = builder
                .with_pos_and_size(glm::ivec2 { 0, 0 }, glm::ivec2 { global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y })
                .with_child<PlaneComponent>([](ComponentBuilder<PlaneComponent> &builder) {
                    builder.with_rel_pos_and_size(glm::ivec2{20, 20}, glm::ivec2{220, 200})
                            .with_background({0.3f, 0.3f, 0.3f, 1.0f})
                            .with_border(2, { 1.0f, 1.0f, 1.0, 1.0f})
                            .with_child<TextComponent>([](ComponentBuilder<TextComponent> &builder) {
                                builder.with_rel_pos_and_size({ 0, 0}, { 100, 14 })
                                    .with_text("Wow this is cool!", 14);
                            })
                            .with_child<ButtonComponent>({ 10, 10 }, { 130, 40 });
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

    bool UI::on_mouse_move(UIComponent *component, UIMouseMoveEvent event) {
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

        bool hovers_child;
        for (auto &child : component_ref.children) {
            hovers_child = on_mouse_move(child.get(), event);
        }

        // We want to fire the event only at the deepest, because the event will be bubbled up
        if (!hovers_child) {
            component_ref.handle_event(UIEventType::MouseMove, &event);
        }

        return true;
    }

    bool UI::on_click(UIComponent *component, UIMouseClickEvent event) const {
        auto &component_ref = *component;

        bool clicks_component = false;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            clicks_component = true;
        }

        if (!clicks_component) {
            return false;
        }

        bool clicks_child = false;
        for (auto &child : component_ref.children) {
            clicks_child = on_click(child.get(), event);
        }

        if (!clicks_child) {
            component_ref.handle_event(UIEventType::MouseButton, &event);
        }

        return true;
    }
}