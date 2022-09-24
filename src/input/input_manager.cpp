#include "input_manager.h"
#include "input.h"
#include "../global.h"
#include "../game/game_state.h"

namespace input {
    InputManager::InputManager() {
        mouseEventHandler = core::create_unique_event_handler<input::MouseEvent>(
               [&](const input::MouseEvent &event) { on_mouse_movement(event.mouse_x_offset, event.mouse_y_offset); });

        keyEventHandler = core::create_unique_event_handler<input::KeyEvent>(
               [&](const input::KeyEvent &event) { on_key_event(event.key, event.mods, event.action); });
    }

    void InputManager::on_mouse_movement(float mouse_x_offset, float mouse_y_offset) {
        entity::RotateCommand command;
        command.degrees_x = mouse_x_offset * settings.mouse_sensitivity;
        command.degrees_y = mouse_y_offset * settings.mouse_sensitivity;

        command.execute(global.game->player);
    }

    void InputManager::on_key_event(int key, int mods_mask, int action) {
        if (action == input::KEY_PRESS || action == input::KEY_RELEASE) {
            switch(key) {
                case input::KEY_W:
                    // moves_forward = action == input::KEY_PRESS;
                    break;
                case input::KEY_S:
                    // moves_backward = action == input::KEY_PRESS;
                    break;
                case input::KEY_A:
                    // moves_left = action == input::KEY_PRESS;
                    break;
                case input::KEY_D:
                    // moves_right = action == input::KEY_PRESS;
                    break;
                default:
                    break;
            }
        }
    }
}
