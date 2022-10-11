#pragma once

#include "component.h"

#include "../input/input.h"
#include "events.h"
#include "view.h"
#include <array>

namespace ui {
    class UI {
    public:
        UI();
        std::unique_ptr<UiElement> root;

        void handle_mouse_move_event();
        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render();
        void on_tick(uint64_t tick);

        void open_dev_info();
        void open_edit_tools();
    private:
        View view;
    };
}