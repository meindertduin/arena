#pragma once

#include "component.h"

#include "../input/input.h"

namespace ui {

    struct UIMouseClickEvent {
        uint32_t button;
        glm::ivec2 mouse_pos;
    };

    class UI {
    public:
        UI();
        std::unique_ptr<ui::UIComponent> root;

        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render() const;
    };
}