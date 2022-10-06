#include "ui.h"
#include "../global.h"
#include "component_builder.h"
#include "../graphics/ui_renderer.h"

namespace ui {
    UI::UI() {
        root = std::make_unique<RootElement>(glm::ivec2 { 0, 0 }, glm::ivec2 {  global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y });
        root->background_color = { 0.1f, 0.1f, 0.1f, 0.25f };
        auto info = std::make_unique<TextElement>(glm::ivec2 { 10, 10}, glm::ivec2 { 100, 50 }, "Hello world");
        info->background_color = { 1, 0, 0, 1 };
        info->parent = root.get();
        root->children.push_back(std::move(info));
    }

    void UI::handle_mouse_move_event() {
        // auto mouse_pos = input::get_mouse_position();
        // UIMouseMoveEvent event = { .mouse_pos = mouse_pos };
        // on_mouse_move(root.get(), event);
    }

    void UI::handle_mouse_button_event(const input::KeyCombination &combi) {
        // if (combi.action == input::KEY_PRESS) {
        //     auto mouse_pos = input::get_mouse_position();
        //     UIMouseClickEvent event = { .button = combi.key, .mouse_pos = mouse_pos };
        //     on_click(root.get(), event);
        // }
    }

    void UI::handle_key_event(const input::KeyCombination &combi) {
        // TODO implement
    }

    void UI::render() {
        global.ui_renderer->before_ui_rendering();
        global.ui_renderer->render(root.get());
        global.ui_renderer->after_ui_rendering();
    }

    bool UI::on_mouse_move(UIComponent *component, UIMouseMoveEvent &event) {
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

    bool UI::on_click(UIComponent *component, UIMouseClickEvent &event) const {
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

    void UI::open_dev_info() {
        // ComponentBuilder<RootComponent> builder;
        // root.reset();
        // root = builder
        //         .with_pos_and_size(glm::ivec2 { 0, 0 }, glm::ivec2 { global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y })
        //         .with_child<DebugPanelComponent>({ 10, 10}, { 200, 100 })
        //         .build();
    }

    void UI::open_edit_tools() {
        // ComponentBuilder<RootComponent> builder;
        // root.reset();
        // root = builder
        //         .with_pos_and_size(glm::ivec2 { 0, 0 }, glm::ivec2 { global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y })
        //         .with_child<DebugPanelComponent>({ 100, 100}, { 200, 100 })
        //         .build();
    }
}
