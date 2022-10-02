#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>

namespace core {
    struct WindowOptions {
        uint32_t width;
        uint32_t height;
        std::string window_name;
        bool cursor_enabled = false;
    };

    struct Window {
    public:
        explicit Window(const WindowOptions &options);
        ~Window();

        [[nodiscard]] bool close_requested() const;
        void end_frame() const;
        void enable_cursor();
        void disable_cursor();
        void poll_events() const;

        WindowOptions win_options;

        GLFWwindow *window;
    };
}
