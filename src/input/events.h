#pragma once

#include "../core/event.h"
#include "input.h"

namespace input {
    struct KeyEvent : public core::Event {
        KeyCombination key_combination;
    };

    struct MouseEvent : public core::Event {
        float mouse_x;
        float mouse_y;
        float mouse_x_offset;
        float mouse_y_offset;
    };
}
