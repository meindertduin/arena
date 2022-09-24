#pragma once

#include <unordered_map>
#include <optional>
#include <memory>

#include "../entity/ec_command.h"
#include "input.h"

namespace input {
    class Keybindings {
    public:
        // TODO Load these from file
        Keybindings();

        Keybindings(const Keybindings &other) = delete;
        Keybindings& operator=(const Keybindings &other) = delete;

        std::optional<entity::ECCommand*> get_command(const KeyCombination &combination);
    private:
        std::unordered_map<uint32_t , std::unique_ptr<entity::ECCommand>> commands;
    };
}