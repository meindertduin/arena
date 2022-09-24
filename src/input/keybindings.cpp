#include "key_bindings.h"

namespace input {
    Keybindings::Keybindings() {
        player_commands.insert({ KeyCombination{KEY_W, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Forward) });
        player_commands.insert({ KeyCombination{KEY_W, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Forward) });

        player_commands.insert({ KeyCombination{KEY_S, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Backward) });
        player_commands.insert({ KeyCombination{KEY_S, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Backward) });

        player_commands.insert({ KeyCombination{KEY_A, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Left) });
        player_commands.insert({ KeyCombination{KEY_A, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Left) });

        player_commands.insert({ KeyCombination{KEY_D, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Right) });
        player_commands.insert({ KeyCombination{KEY_D, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Right) });

        ui_commands.insert({ KeyCombination{KEY_ESCAPE, 0, KEY_PRESS}.to_u32(), std::make_unique<ui::ToggleOverlayCommand>() });
    }

    std::optional<entity::ECCommand*> Keybindings::get_player_command(const KeyCombination &combination) {
        auto combo_u32 = combination.to_u32();
        if (player_commands.find(combo_u32) == player_commands.end())
            return std::nullopt;

        auto &command = player_commands[combo_u32];
        return std::optional<entity::ECCommand*>{command.get()};
    }

    std::optional<ui::UICommand *> Keybindings::get_ui_command(const KeyCombination &combination) {
        auto combo_u32 = combination.to_u32();
        if (ui_commands.find(combo_u32) == ui_commands.end())
            return std::nullopt;

        auto &command = ui_commands[combo_u32];
        return std::optional<ui::UICommand*>{command.get()};
    }
}