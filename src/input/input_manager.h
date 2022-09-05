#pragma once

#include <memory>

#include "events.h"
#include "../core/event_dispatcher.h"

#include "../entity/ec_command.h"

namespace input {

    struct PlayerInput {
    public:
        struct PlayerInputSettings {
            float mouse_sensitivity = 0.1f;
            PlayerInputSettings() = default;
        };

        PlayerInputSettings settings;

        PlayerInput() = default;

        void update();
        void on_mouse_movement(float mouse_x_offset, float mouse_y_offset);
        void on_key_press(int key, int mod_mask, int action);
    private:
        bool moves_forward = false;
        bool moves_backward = false;
        bool moves_left = false;
        bool moves_right = false;
    };

    struct InputManager {
    public:
        InputManager();

        void update();
        void on_mouse_movement(float mouse_x_offset, float mouse_y_offset);
        void on_key_event(int key, int mods_mask, int action);
    private:
        std::unique_ptr<core::EventHandler<input::MouseEvent>> mouseEventHandler;
        std::unique_ptr<core::EventHandler<input::KeyEvent>> keyEventHandler;

        PlayerInput player_input;
    };
}
