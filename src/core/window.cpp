#include "window.h"
#include <glad/glad.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

namespace core {
    Window::Window(const WindowOptions &options) {
        this->win_options = options;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        pm_window = glfwCreateWindow(options.width, options.height, options.window_name.c_str(), nullptr, nullptr);
        if (pm_window == nullptr) {
            glfwTerminate();
        }

        // glfwSetInputMode(pm_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(pm_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glfwMakeContextCurrent(pm_window);
        glfwSetFramebufferSizeCallback(pm_window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            printf("Couldnt setup GLAD\n");
        }

        // setup imGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(pm_window, true);

        // TODO parse the actual openGL version
        const char* glsl_version = "#version 330";
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImGui::StyleColorsDark();
    }

    Window::~Window() {
        glfwDestroyWindow(pm_window);
        glfwTerminate();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool Window::close_requested() const  {
        return glfwWindowShouldClose(pm_window);
    }

    void Window::poll_events() const {
        glfwPollEvents();
    }

    void Window::end_frame() const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(pm_window);
    }

    void Window::enable_cursor() {
        if (win_options.cursor_enabled)
            return;

        win_options.cursor_enabled = true;
        glfwSetInputMode(pm_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::disable_cursor() {
        if (!win_options.cursor_enabled)
            return;

        win_options.cursor_enabled = false;
        glfwSetInputMode(pm_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
