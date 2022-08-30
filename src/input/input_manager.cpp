#include "input_manager.h"
#include "input.h"

namespace input {
    InputManager::InputManager() {
        mouseEventHandler = core::create_unique_event_handler<input::MouseEvent>(
               [&](const input::MouseEvent &event) { on_mouse_movement(event.mouse_x_offset, event.mouse_y_offset); });

        keyEventHandler = core::create_unique_event_handler<input::KeyEvent>(
               [&](const input::KeyEvent &event) { on_key_event(event.key, event.mods, event.action); });
    }

    void InputManager::update() {
        
    }

    void InputManager::on_mouse_movement(float mouse_x_offset, float mouse_y_offset) {
        // TODO check state of program
        this->player_input.on_mouse_movement(mouse_x_offset, mouse_y_offset);
    }

    void InputManager::on_key_event(int key, int mods_mask, int action) {
        // TODO check state of program
        this->player_input.on_key_press(key, mods_mask, action);
    }

    void PlayerInput::update() {
        if (moves_forward && !moves_backward) {

        } else if (moves_backward && !moves_forward) {

        }

        if (moves_right && !moves_left) {

        } else if (moves_left && !moves_right) {

        }
    }

    void PlayerInput::on_mouse_movement(float mouse_x_offset, float mouse_y_offset) {
        auto xoffset = mouse_x_offset;
        auto yoffset = mouse_y_offset;

        xoffset *= settings.mouse_sensitivity;
        yoffset *= settings.mouse_sensitivity;
    }

    void PlayerInput::on_key_press(int key, int mod_mask, int action) {
        if (action == input::KEY_PRESS || action == input::KEY_RELEASE) {
            switch(key) {
                case input::KEY_W:
                    moves_forward = action == input::KEY_PRESS;
                    break;
                case input::KEY_S:
                    moves_backward = action == input::KEY_PRESS;
                    break;
                case input::KEY_A:
                    moves_left = action == input::KEY_PRESS;
                    break;
                case input::KEY_D:
                    moves_right = action == input::KEY_PRESS;
                    break;
                default:
                    break;
            }
        }
    }
}
