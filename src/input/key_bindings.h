#pragma once

#include <unordered_map>
#include <optional>
#include <memory>

#include "../entity/ec_command.h"
#include "../ui/ui_command.h"
#include "input.h"

namespace input {
    class Keybindings {
    public:
        // TODO Load these from file
        Keybindings();

        Keybindings(const Keybindings &other) = delete;
        Keybindings& operator=(const Keybindings &other) = delete;

        // TODO rule of 3: Can be template functions with specializations
        std::optional<entity::ECCommand*> get_player_command(const KeyCombination &combination);
        std::optional<ui::UICommand*> get_ui_command(const KeyCombination &combination);
    private:
        std::unordered_map<uint32_t , std::unique_ptr<entity::ECCommand>> player_commands;
        std::unordered_map<uint32_t , std::unique_ptr<ui::UICommand>> ui_commands;
    };
}