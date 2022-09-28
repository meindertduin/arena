#pragma once

#include "component.h"

#include "../input/input.h"
#include <array>

namespace ui {
    struct UIEvent {
        bool stop_bubbling { false };
    };

    struct UIMouseClickEvent : public UIEvent {
        uint32_t button;
        glm::ivec2 mouse_pos;
    };

    struct UIMouseMoveEvent : public UIEvent {
        glm::ivec2 mouse_pos;
    };

    class UI {
    public:
        UI();
        std::unique_ptr<UIComponent> root;

        void handle_mouse_move_event();
        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render();
    private:
        // TODO optimize the events, i.e. passed by reference hopefully
        bool on_mouse_move(UIComponent *component, UIMouseMoveEvent event);
        bool on_click(UIComponent *component, UIMouseClickEvent event) const;
    };
}