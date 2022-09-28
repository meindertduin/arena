#pragma once

#include "../core/window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <array>
#include <glm/glm.hpp>

namespace input {
    constexpr int KEY_PRESS = GLFW_PRESS;
    constexpr int KEY_RELEASE = GLFW_RELEASE;

    constexpr int KEY_0 = GLFW_KEY_0;
    constexpr int KEY_1 = GLFW_KEY_1;
    constexpr int KEY_2 = GLFW_KEY_2;
    constexpr int KEY_3 = GLFW_KEY_3;
    constexpr int KEY_4 = GLFW_KEY_4;
    constexpr int KEY_5 = GLFW_KEY_5;
    constexpr int KEY_6 = GLFW_KEY_6;
    constexpr int KEY_7 = GLFW_KEY_7;
    constexpr int KEY_8 = GLFW_KEY_8;
    constexpr int KEY_9 = GLFW_KEY_9;

    constexpr int KEY_A = GLFW_KEY_A;
    constexpr int KEY_B = GLFW_KEY_B;
    constexpr int KEY_C = GLFW_KEY_C;
    constexpr int KEY_D = GLFW_KEY_D;
    constexpr int KEY_E = GLFW_KEY_E;
    constexpr int KEY_F = GLFW_KEY_F;
    constexpr int KEY_G = GLFW_KEY_G;
    constexpr int KEY_H = GLFW_KEY_H;
    constexpr int KEY_I = GLFW_KEY_I;
    constexpr int KEY_J = GLFW_KEY_J;
    constexpr int KEY_K = GLFW_KEY_K;
    constexpr int KEY_L = GLFW_KEY_L;
    constexpr int KEY_M = GLFW_KEY_M;
    constexpr int KEY_N = GLFW_KEY_N;
    constexpr int KEY_O = GLFW_KEY_O;
    constexpr int KEY_P = GLFW_KEY_P;
    constexpr int KEY_Q = GLFW_KEY_Q;
    constexpr int KEY_R = GLFW_KEY_R;
    constexpr int KEY_S = GLFW_KEY_S;
    constexpr int KEY_T = GLFW_KEY_T;
    constexpr int KEY_U = GLFW_KEY_U;
    constexpr int KEY_V = GLFW_KEY_V;
    constexpr int KEY_W = GLFW_KEY_W;
    constexpr int KEY_X = GLFW_KEY_X;
    constexpr int KEY_Y = GLFW_KEY_Y;
    constexpr int KEY_Z = GLFW_KEY_Z;

    constexpr int KEY_ESCAPE = GLFW_KEY_ESCAPE;
    constexpr int KEY_ENTER = GLFW_KEY_ENTER;
    constexpr int KEY_TAB = GLFW_KEY_TAB;
    constexpr int KEY_BACKSPACE = GLFW_KEY_BACKSPACE;
    constexpr int KEY_INSERT = GLFW_KEY_INSERT;
    constexpr int KEY_DELETE = GLFW_KEY_DELETE;
    constexpr int KEY_RIGHT = GLFW_KEY_RIGHT;
    constexpr int KEY_LEFT = GLFW_KEY_LEFT;
    constexpr int KEY_DOWN = GLFW_KEY_DOWN;
    constexpr int KEY_UP = GLFW_KEY_UP;
    constexpr int KEY_PAGE_UP = GLFW_KEY_PAGE_UP;
    constexpr int KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
    constexpr int KEY_HOME = GLFW_KEY_HOME;
    constexpr int KEY_END = GLFW_KEY_END;
    constexpr int KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
    constexpr int KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;
    constexpr int KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK;
    constexpr int KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN;
    constexpr int KEY_PAUSE = GLFW_KEY_PAUSE;

    constexpr int KEY_F1 = GLFW_KEY_F1;
    constexpr int KEY_F2 = GLFW_KEY_F2;
    constexpr int KEY_F3 = GLFW_KEY_F3;
    constexpr int KEY_F4 = GLFW_KEY_F4;
    constexpr int KEY_F5 = GLFW_KEY_F5;
    constexpr int KEY_F6 = GLFW_KEY_F6;
    constexpr int KEY_F7 = GLFW_KEY_F7;
    constexpr int KEY_F8 = GLFW_KEY_F8;
    constexpr int KEY_F9 = GLFW_KEY_F9;
    constexpr int KEY_F10 = GLFW_KEY_F10;
    constexpr int KEY_F11 = GLFW_KEY_F11;
    constexpr int KEY_F12 = GLFW_KEY_F12;
    constexpr int KEY_F13 = GLFW_KEY_F13;
    constexpr int KEY_F14 = GLFW_KEY_F14;
    constexpr int KEY_F15 = GLFW_KEY_F15;
    constexpr int KEY_F16 = GLFW_KEY_F16;
    constexpr int KEY_F17 = GLFW_KEY_F17;
    constexpr int KEY_F18 = GLFW_KEY_F18;
    constexpr int KEY_F19 = GLFW_KEY_F19;
    constexpr int KEY_F20 = GLFW_KEY_F20;
    constexpr int KEY_F21 = GLFW_KEY_F21;
    constexpr int KEY_F22 = GLFW_KEY_F22;
    constexpr int KEY_F23 = GLFW_KEY_F23;
    constexpr int KEY_F24 = GLFW_KEY_F24;
    constexpr int KEY_F25 = GLFW_KEY_F25;
    constexpr int KEY_KP_0 = GLFW_KEY_KP_0;
    constexpr int KEY_KP_1 = GLFW_KEY_KP_1;
    constexpr int KEY_KP_2 = GLFW_KEY_KP_2;
    constexpr int KEY_KP_3 = GLFW_KEY_KP_3;
    constexpr int KEY_KP_4 = GLFW_KEY_KP_4;
    constexpr int KEY_KP_5 = GLFW_KEY_KP_5;
    constexpr int KEY_KP_6 = GLFW_KEY_KP_6;
    constexpr int KEY_KP_7 = GLFW_KEY_KP_7;
    constexpr int KEY_KP_8 = GLFW_KEY_KP_8;
    constexpr int KEY_KP_9 = GLFW_KEY_KP_9;
    constexpr int KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL;
    constexpr int KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE;
    constexpr int KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
    constexpr int KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
    constexpr int KEY_KP_ADD = GLFW_KEY_KP_ADD;
    constexpr int KEY_KP_ENTER = GLFW_KEY_KP_ENTER;
    constexpr int KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL;
    constexpr int KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
    constexpr int KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
    constexpr int KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT;
    constexpr int KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER;
    constexpr int KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
    constexpr int KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL;
    constexpr int KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
    constexpr int KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER;
    constexpr int KEY_MENU = GLFW_KEY_MENU;

    constexpr int MAX_KEYBOARD_NUM = GLFW_KEY_MENU;

    constexpr int MOUSE_1 = GLFW_MOUSE_BUTTON_1;
    constexpr int MOUSE_2 = GLFW_MOUSE_BUTTON_2;
    constexpr int MOUSE_3 = GLFW_MOUSE_BUTTON_3;
    constexpr int MOUSE_4 = GLFW_MOUSE_BUTTON_4;
    constexpr int MOUSE_5 = GLFW_MOUSE_BUTTON_5;
    constexpr int MOUSE_6 = GLFW_MOUSE_BUTTON_6;
    constexpr int MOUSE_7 = GLFW_MOUSE_BUTTON_7;
    constexpr int MOUSE_8 = GLFW_MOUSE_BUTTON_8;

    constexpr int MOD_ALT = GLFW_MOD_ALT;
    constexpr int MOD_CONTROL = GLFW_MOD_CONTROL;
    constexpr int MOD_CAPS_LOCK = GLFW_MOD_CAPS_LOCK;
    constexpr int MOD_SHIFT = GLFW_MOD_SHIFT;
    constexpr int MOD_SUPER = GLFW_MOD_SUPER;
    constexpr int MOD_NUM_LOCK = GLFW_MOD_NUM_LOCK;

    struct KeyCombination {
        uint32_t key;
        uint32_t mods_mask;
        uint32_t action;

        KeyCombination() = default;
        KeyCombination(uint32_t key, uint32_t mods_mask, uint32_t action) : key{key}, mods_mask{mods_mask}, action{action} { }

        inline auto operator==(const KeyCombination &rhs) const {
            return key == rhs.key && mods_mask == rhs.mods_mask && action == rhs.action;
        }

        [[nodiscard]] constexpr uint32_t to_u32() const {
            return (key << 16) | (mods_mask << 8) | action;
        }
    };

    inline static std::array<int, MAX_KEYBOARD_NUM> keyboard_state;

    void initialize_input(const core::Window &window);
    glm::ivec2 get_mouse_position();
    void get_mouse_movement(int &dx, int &dy);
    int get_pressed_keys();
}
