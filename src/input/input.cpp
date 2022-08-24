#include "input.h"


#include "../core/event_dispatcher.h"
#include "events.h"

namespace input {
    static bool first_mouse = false;
    static float mouse_x;
    static float mouse_y;

    static float mouse_x_offset;
    static float mouse_y_offset;


    void initialize_input(const core::Window &window) {
        keyboard_state.fill(0);

        glfwSetKeyCallback(window.window,
                [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            auto dispatcher = core::EventDispatcher<KeyEvent>::instance();

            if (action == KEY_PRESS) {
                keyboard_state[key] = 1;
            } else if(action == KEY_RELEASE) {
                keyboard_state[key] = 0;
            }

            KeyEvent event;
            event.event_type = core::Event::EventType::InputEvent;
            event.key = key;
            event.mods = mods;
            event.action = action;

            dispatcher->emit_event(event);
        });

        glfwSetCursorPosCallback(window.window,
                [](GLFWwindow* window, double xposIn, double yposIn)
        {
            float xpos = static_cast<float>(xposIn);
            float ypos = static_cast<float>(yposIn);

            if (first_mouse)
            {
                mouse_x = xpos;
                mouse_y = ypos;
                first_mouse = false;
            }

            mouse_x_offset = xpos - mouse_x;
            mouse_y_offset = mouse_y - ypos; // reversed since y-coordinates go from bottom to top

            mouse_x = xpos;
            mouse_y = ypos;

            auto dispatcher = core::EventDispatcher<MouseEvent>::instance();
            MouseEvent event;
            event.event_type = core::Event::EventType::InputEvent;
            event.mouse_x = mouse_x;
            event.mouse_y = mouse_y;
            event.mouse_x_offset = mouse_x_offset;
            event.mouse_y_offset = mouse_y_offset;

            dispatcher->emit_event(event);
        });

    }

    void get_mouse_position(int &xPos, int &yPos) {
        xPos = mouse_x;
        yPos = mouse_y;
    }

    void get_mouse_movement(int &dx, int &dy) {
        dx = mouse_x_offset;
        dy = mouse_y_offset;
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
