#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>
#include "../platform/platform.h"

namespace core {
    struct WindowOptions {
        uint32_t width;
        uint32_t height;
        std::string window_name;
        bool cursor_enabled = false;
    };

    class Window {
    public:
        explicit Window(const WindowOptions &options);
        ~Window();

        [[nodiscard]] bool close_requested() const;
        void end_frame() const;
        void enable_cursor();
        void disable_cursor();
        void poll_events() const;

        [[nodiscard]] ALWAYS_INLINE GLFWwindow* window() const { return pm_window; }
    private:
        WindowOptions win_options;
        GLFWwindow *pm_window;
    };
}

