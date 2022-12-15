#include "ui_command.h"

#include "../global.h"
#include "../game/game_state.h"

namespace ui {
    void ToggleOverlayCommand::execute() {
        auto game = global.application->engine()->game();
        if (game->ui_mode()) {
            game->set_ui_mode(false);
            global.application->window()->disable_cursor();
        } else {
            game->ui().open_dev_info();
            game->set_ui_mode(true);
            global.application->window()->enable_cursor();
        }
    }

    void ToggleEditModeCommand::execute() {
        // TODO test code
        global.application->window()->enable_cursor();
    }
}