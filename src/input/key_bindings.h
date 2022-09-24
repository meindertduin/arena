#pragma once

#include <unordered_map>
#include <optional>

#include "../core/command.h"
#include "input.h"

namespace input {
    class Keybindings {
    public:
        // TODO Load these from file
        Keybindings();
        std::optional<core::Command*> get_command(const KeyCombination &combination);
    private:
        std::unordered_map<uint32_t , core::Command*> commands;
    };

}