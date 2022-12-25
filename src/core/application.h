#pragma once

#include <memory>
#include "program_time.h"
#include "../platform/platform.h"
#include "engine.h"

namespace core {
    class Window;
}

namespace graphics {
    class Renderer;
}

class Application {
public:
    ~Application();

    void initialize();
    void run();

    [[nodiscard]] constexpr ALWAYS_INLINE core::Window* window() const {
        return m_window;
    }

    [[nodiscard]] constexpr ALWAYS_INLINE core::Engine* engine() const {
        return m_engine;
    }

    [[nodiscard]] constexpr ALWAYS_INLINE graphics::Renderer* renderer() const {
        return m_renderer;
    }

private:
    bool m_initialized { false };
    bool m_editor { true };

    core::Timer m_program_timer;

    core::Window *m_window { nullptr };
    core::Engine *m_engine { nullptr };
    graphics::Renderer *m_renderer { nullptr };
};