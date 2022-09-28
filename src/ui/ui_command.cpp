#include "ui_command.h"

#include "../global.h"
#include "../game/game_state.h"

namespace ui {
    void ToggleOverlayCommand::execute() {
        if (global.game->ui_mode) {
            global.game->ui_mode = false;
            global.window->disable_cursor();
        } else {
            global.game->ui_mode = true;
            global.window->enable_cursor();
        }
    }
}