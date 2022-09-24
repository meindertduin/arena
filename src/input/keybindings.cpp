#include "key_bindings.h"

namespace input {
    Keybindings::Keybindings() {
        commands.insert({ KeyCombination{0,0,0}.to_u32(), nullptr });
    }

    std::optional<core::Command*> Keybindings::get_command(const KeyCombination &combination) {
        auto combo_u32 = combination.to_u32();
        if (commands.find(combo_u32) == commands.end())
            return std::nullopt;

        return std::optional<core::Command*>{commands[combo_u32]};
    }
}