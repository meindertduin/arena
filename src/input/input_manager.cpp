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

        mouse_button_event_handler = core::create_unique_event_handler<input::MouseButtonEvent>(
                [&](const input::MouseButtonEvent &event) { on_mouse_button_event(event.key_combination); });
    }

    void InputManager::on_mouse_movement(float mouse_x_offset, float mouse_y_offset) const {
        auto game = global.application->engine()->game();

        entity::RotateCommand command;
        command.degrees_x = mouse_x_offset * settings.mouse_sensitivity;
        command.degrees_y = mouse_y_offset * settings.mouse_sensitivity;

        command.execute(game->active_scene()->player());
    }

    void InputManager::on_mouse_button_event(KeyCombination combi) {
        // TODO implement
    }

    void InputManager::on_key_event(KeyCombination combi) {
        auto maskless_combi = combi;
        maskless_combi.mods_mask = 0;

        handle_player_command(combi, maskless_combi);
    }

    bool InputManager::handle_player_command(const KeyCombination &combi, const KeyCombination &maskless_combi) {
        auto game = global.application->engine()->game();
        auto maskless_command_opt = key_bindings.get_player_command(maskless_combi);
        if (maskless_command_opt.has_value()) {
            maskless_command_opt.value()->execute(game->active_scene()->player());
            return true;
        }

        auto command_opt = key_bindings.get_player_command(combi);
        if (command_opt.has_value()) {
            command_opt.value()->execute(game->active_scene()->player());
            return true;
        }

        return false;
    }
}