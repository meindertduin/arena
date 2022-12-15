#include "application.h"

// Shared imports
#include "../global.h"
#include "../game/game_state.h"
#include "../graphics/font.h"

// Editor imports
#include "../editor/editor.h"

// Game imports

void Application::initialize() {
    Logger::debug("Initializing application");

    graphics::font_init();
    global.init();
}

void Application::run() {
    Logger::debug("Starting application");

    int lag;
    while(!global.window->close_requested()) {
        lag += m_program_timer.difference_ms();
        m_program_timer.start();
        global.window->poll_events();

        if (m_editor) {
            global.editor->update();
        }

        while (lag >= core::TickTimeMs) {
            global.game->update();

            core::TotalTicks++;
            lag -= core::TickTimeMs;
        }

        global.game->render();
        global.window->end_frame();

        auto difference_ms = m_program_timer.get_time_ms();
        int delay_time_ms = static_cast<int>(1000.0f / 60.0f) - difference_ms;
        global.telemetrics.last_frame_time_ms = difference_ms;

        if (delay_time_ms > 0) {
            core::delay(delay_time_ms);
        }

        m_program_timer.stop();
    }
}

Application::~Application() {
    graphics::font_quit();
}
