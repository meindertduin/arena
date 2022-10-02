#include "window.h"
#include <glad/glad.h>

namespace core {
    Window::Window(const WindowOptions &options) {
        this->win_options = options;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(options.width, options.height, options.window_name.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            glfwTerminate();
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            printf("Couldnt setup GLAD\n");
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool Window::close_requested() const  {
        return glfwWindowShouldClose(window);
    }

    void Window::poll_events() const {
        glfwPollEvents();
    }

    void Window::end_frame() const {
        glfwSwapBuffers(window);
    }

    void Window::enable_cursor() {
        if (win_options.cursor_enabled)
            return;

        win_options.cursor_enabled = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::disable_cursor() {
        if (!win_options.cursor_enabled)
            return;

        win_options.cursor_enabled = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
