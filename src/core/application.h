#pragma once

#include <memory>
#include "program_time.h"
#include "window.h"

class Application {
public:
    ~Application();

    void initialize();
    void run();

    constexpr ALWAYS_INLINE
    std::unique_ptr<core::Window>& window() {
        return m_window;
    }

private:
    bool m_initialized { false };
    bool m_editor { true };

    core::Timer m_program_timer;

    std::unique_ptr<core::Window> m_window;
};