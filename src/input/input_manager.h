#pragma once

#include <memory>

#include "events.h"
#include "../core/event_dispatcher.h"

#include "../entity/ec_command.h"
#include "key_bindings.h"

namespace input {
    class InputManager {
    public:
        InputManager();

        void on_mouse_movement(float mouse_x_offset, float mouse_y_offset) const;
        static void on_mouse_button_event(KeyCombination combi);
        void on_key_event(KeyCombination combi);
    private:
        std::unique_ptr<core::EventHandler<input::MouseEvent>> mouseEventHandler;
        std::unique_ptr<core::EventHandler<input::KeyEvent>> keyEventHandler;
        std::unique_ptr<core::EventHandler<input::MouseButtonEvent>> mouse_button_event_handler;

        struct InputSettings {
            float mouse_sensitivity = 0.1f;
            InputSettings() = default;
        } settings;

        Keybindings key_bindings;

        bool handle_player_command(const KeyCombination &combi, const KeyCombination &maskless_combi);
    };
}
