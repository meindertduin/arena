#include "application.h"

#include "../global.h"
#include "../graphics/font.h"
#include "../editor/editor.h"
#include "../logging.h"
#include "window.h"
#include "engine.h"
#include "../graphics/renderer.h"

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

    global.application = this;
    global.graphic_options = new graphics::GraphicOptions {
            true,
            { 640, 480 },
    };

    m_window = new core::Window(window_options);
    m_engine = new core::Engine();

    auto render_target = std::make_shared<graphics::RenderTarget>();
    m_renderer = new graphics::Renderer(render_target);

    m_engine->initialize();

    global.init();

    input::initialize_input(m_window);

    m_initialized = true;
}

void Application::run() {
    assert(m_initialized && m_window != nullptr);

    Logger::debug("Starting application");

    int lag;
    while(!m_window->close_requested()) {
        lag = m_program_timer.difference_ms();
        m_program_timer.start();
        m_window->poll_events();

        if (m_editor) {
            global.editor->update();
        }

        m_engine->update(lag);

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

