#include "input.h"

#include "../core/event_dispatcher.h"
#include "events.h"
#include "../graphics/graphic_options.h"
#include "imgui/imgui_impl_glfw.h"

namespace input {
    static float mouse_x;
    static float mouse_y;

    static float mouse_x_offset;
    static float mouse_y_offset;

    void initialize_input(core::Window *window) {
        keyboard_state.fill(0);

        glfwSetKeyCallback(window->window(),
                [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            auto dispatcher = core::EventDispatcher<KeyEvent>::instance();

            if (action == KEY_PRESS) {
                keyboard_state[key] = 1;
            } else if(action == KEY_RELEASE) {
                keyboard_state[key] = 0;
            }

            KeyEvent event{};
            event.event_type = core::Event::EventType::InputEvent;
            event.key_combination = KeyCombination(key, mods, action);

            dispatcher->emit_event(event);

            ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        });

        glfwSetMouseButtonCallback(window->window(), [](GLFWwindow *window, int button, int action, int mods) {
            auto dispatcher = core::EventDispatcher<MouseButtonEvent>::instance();

            MouseButtonEvent event{};
            event.event_type = core::Event::EventType::InputEvent;
            event.key_combination = KeyCombination(button, mods, action);

            dispatcher->emit_event(event);

            ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        });

        glfwSetCursorPosCallback(window->window(),
                [](GLFWwindow* window, double xpos_in, double ypos_in)
        {
            auto xpos = static_cast<float>(xpos_in);
            auto ypos = static_cast<float>(ypos_in);

            mouse_x_offset = xpos - mouse_x;
            mouse_y_offset = mouse_y - ypos; // reversed since y-coordinates go from bottom to top

            mouse_x = xpos;
            mouse_y = ypos;

            auto dispatcher = core::EventDispatcher<MouseEvent>::instance();
            MouseEvent event{};
            event.event_type = core::Event::EventType::InputEvent;
            event.mouse_x = mouse_x;
            event.mouse_y = mouse_y;
            event.mouse_x_offset = mouse_x_offset;
            event.mouse_y_offset = mouse_y_offset;

            dispatcher->emit_event(event);

            ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
        });

    }

    glm::ivec2 get_mouse_position() {
        return { static_cast<int>(mouse_x), static_cast<int>(mouse_y) };
    }

    void get_mouse_movement(int &dx, int &dy) {
        dx = static_cast<int>(mouse_x_offset);
        dy = static_cast<int>(mouse_y_offset);
    }

    int get_pressed_keys() {
        int pressed_keys = 0;

        for (int i = 0; i < MAX_KEYBOARD_NUM; i++) {
            if (keyboard_state[i]) {
                pressed_keys |= i;
            }
        }

        return pressed_keys;
    }
}
