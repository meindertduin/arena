#include "key_bindings.h"

namespace input {
    Keybindings::Keybindings() {
        commands.insert({ KeyCombination{KEY_W, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Forward) });
        commands.insert({ KeyCombination{KEY_W, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Forward) });

        commands.insert({ KeyCombination{KEY_S, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Backward) });
        commands.insert({ KeyCombination{KEY_S, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Backward) });

        commands.insert({ KeyCombination{KEY_A, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Left) });
        commands.insert({ KeyCombination{KEY_A, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Left) });

        commands.insert({ KeyCombination{KEY_D, 0, KEY_PRESS}.to_u32(), std::make_unique<entity::StartMoveCommand>(entity::Direction::Right) });
        commands.insert({ KeyCombination{KEY_D, 0, KEY_RELEASE}.to_u32(), std::make_unique<entity::StopMoveCommand>(entity::Direction::Right) });
    }

    std::optional<entity::ECCommand*> Keybindings::get_command(const KeyCombination &combination) {
        auto combo_u32 = combination.to_u32();
        if (commands.find(combo_u32) == commands.end())
            return std::nullopt;

        auto &command = commands[combo_u32];
        return std::optional<entity::ECCommand*>{command.get()};
    }
}