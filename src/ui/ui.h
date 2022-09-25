#pragma once

#include "ui_node.h"
#include "../input/input.h"

namespace ui {
    class UI {
    public:
        UI();
        std::unique_ptr<ui::UINode> root;

        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render() const;
    };
}