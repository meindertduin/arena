#pragma once

#include <glm/glm.hpp>

namespace ui {
    struct UIEvent {
        bool stop_bubbling { false };
    };

    struct UIMouseClickEvent : public UIEvent {
        uint32_t button;
        glm::ivec2 mouse_pos;
    };

    struct UIMouseMoveEvent : public UIEvent {
        glm::ivec2 mouse_pos;
    };

}