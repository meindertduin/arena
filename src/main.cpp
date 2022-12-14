#include "global.h"

#include "core/program_time.h"
#include "input/input.h"
#include "game/game_state.h"
#include "graphics/font.h"

#include "editor/editor.h"

Global global;

int main () {
    Logger::debug("Starting application");

    graphics::font_init();

    global.init();

    // input::initialize_input(*global.window);

    core::Timer program_timer;
    int lag;
    while(!global.window->close_requested()) {
        lag += program_timer.difference_ms();
        program_timer.start();
        global.window->poll_events();

        global.editor->update();

        while (lag >= core::TickTimeMs) {
            global.game->update();

            core::TotalTicks++;
            lag -= core::TickTimeMs;
        }

        global.game->render();
        global.window->end_frame();

        auto difference_ms = program_timer.get_time_ms();
        int delay_time_ms = static_cast<int>(1000.0f / 60.0f) - difference_ms;
        global.telemetrics.last_frame_time_ms = difference_ms;

        if (delay_time_ms > 0) {
            core::delay(delay_time_ms);
        }

        program_timer.stop();
    }

    graphics::font_quit();
    return 0;
}
