#pragma once

#include "../input/input.h"
#include "events.h"
#include "frame.h"
#include <array>

namespace ui {
    class UI {
    public:
        UI() = default;
        void handle_mouse_move_event();
        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render();
        void on_tick(uint64_t tick);

        void open_dev_info();
        void open_edit_tools();
    private:
        Frame frame { "Hello world" };
    };
}