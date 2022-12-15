#include "application.h"

// Shared imports
#include "../global.h"
#include "../game/game_state.h"
#include "../graphics/font.h"

// Editor imports
#include "../editor/editor.h"

// Game imports

Application::~Application() {
    if (m_initialized) {
        Logger::debug("Shutting down application");
        graphics::font_quit();
    }
}

void Application::initialize() {
    if (m_initialized) {
        return;
    }

    Logger::debug("Initializing application");

    graphics::font_init();
    // TODO read these from settings
    auto window_options = core::WindowOptions {
            .width = 1280,
            .height = 720,
            .window_name = "Arena"
    };

    m_window = std::make_unique<core::Window>(window_options);

    global.init(this);

    input::initialize_input(m_window);

    m_initialized = true;
}

void Application::run() {
    Logger::debug("Starting application");

    int lag;
    while(!m_window->close_requested()) {
        lag += m_program_timer.difference_ms();
        m_program_timer.start();
        m_window->poll_events();

        if (m_editor) {
            global.editor->update();
        }

        while (lag >= core::TickTimeMs) {
            global.game->update();

            core::TotalTicks++;
            lag -= core::TickTimeMs;
        }

        global.game->render();

        m_window->end_frame();

        auto difference_ms = m_program_timer.get_time_ms();
        int delay_time_ms = static_cast<int>(1000.0f / 60.0f) - difference_ms;
        global.telemetrics.last_frame_time_ms = difference_ms;

        if (delay_time_ms > 0) {
            core::delay(delay_time_ms);
        }

        m_program_timer.stop();
    }
}

