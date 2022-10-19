#include "ui_command.h"

#include "../global.h"
#include "../game/game_state.h"

namespace ui {
    void ToggleOverlayCommand::execute() {
        if (global.game->ui_mode()) {
            global.game->set_ui_mode(false);
            global.window->disable_cursor();
        } else {
            global.game->ui().open_dev_info();
            global.game->set_ui_mode(true);
            global.window->enable_cursor();
        }
    }

    void ToggleEditModeCommand::execute() {
        if (global.game->game_mode() == game::Mode::Playing) {
            global.game->ui().open_edit_tools();
            global.game->set_game_mode(game::Mode::Editing);

            global.game->set_ui_mode(true);
            global.window->enable_cursor();
        } else {
            global.game->set_game_mode(game::Mode::Playing);
            global.game->set_ui_mode(false);
            global.window->disable_cursor();
        }
    }
}