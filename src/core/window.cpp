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

        GLFWwindow* window = glfwCreateWindow(options.width, options.height, options.window_name.c_str(), nullptr, nullptr);
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
}
