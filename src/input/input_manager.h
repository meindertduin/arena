#pragma once

#include <memory>

#include "events.h"
#include "../core/event_dispatcher.h"

#include "../entity/ec_command.h"

namespace input {
    struct InputManager {
    public:
        InputManager();

        void on_mouse_movement(float mouse_x_offset, float mouse_y_offset);
        void on_key_event(int key, int mods_mask, int action);
    private:
        std::unique_ptr<core::EventHandler<input::MouseEvent>> mouseEventHandler;
        std::unique_ptr<core::EventHandler<input::KeyEvent>> keyEventHandler;

        struct InputSettings {
            float mouse_sensitivity = 0.1f;
            InputSettings() = default;
        } settings;
    };
}
