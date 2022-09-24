#include "input_manager.h"
#include "input.h"
#include "../global.h"
#include "../game/game_state.h"

namespace input {
    InputManager::InputManager() {
        mouseEventHandler = core::create_unique_event_handler<input::MouseEvent>(
               [&](const input::MouseEvent &event) { on_mouse_movement(event.mouse_x_offset, event.mouse_y_offset); });

        keyEventHandler = core::create_unique_event_handler<input::KeyEvent>(
               [&](const input::KeyEvent &event) { on_key_event(event.key_combination); });
    }

    void InputManager::on_mouse_movement(float mouse_x_offset, float mouse_y_offset) {
        entity::RotateCommand command;
        command.degrees_x = mouse_x_offset * settings.mouse_sensitivity;
        command.degrees_y = mouse_y_offset * settings.mouse_sensitivity;

        command.execute(global.game->player);
    }

    void InputManager::on_key_event(KeyCombination combi) {
        auto maskless_combi = combi;
        maskless_combi.mods_mask = 0;

        auto maskless_command_opt = key_bindings.get_player_command(maskless_combi);
        if (maskless_command_opt.has_value()) {
            maskless_command_opt.value()->execute(global.game->player);
            return;
        }

        auto command_opt = key_bindings.get_player_command(combi);
        if (command_opt.has_value()) {
            command_opt.value()->execute(global.game->player);
        }
    }
}
