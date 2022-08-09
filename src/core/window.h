#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <string>

namespace core {
    struct WindowOptions {
        uint32_t width;
        uint32_t height;
        std::string window_name;
    };

    struct Window {
    public:
        Window(const WindowOptions &options);
        ~Window();

        WindowOptions win_options;
    private:
        GLFWwindow *window;
    };
}
