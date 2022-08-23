#pragma once

#include "../core/event.h"

namespace input {
    struct KeyEvent : public core::Event {
        int key;
        int mods;
        int action;
    };

    struct MouseEvent : public core::Event {
        float mouse_x;
        float mouse_y;
        float mouse_x_offset;
        float mouse_y_offset;
    };
}
