#pragma once

#include <glm/glm.hpp>

#include "../core/event.h"
#include "../core/event_dispatcher.h"

namespace graphics {
    struct OptionChangeEvent : public core::Event {
        enum class OptionType {
            Antialiasing,
            ScreenResize,
        } option_type;
    };

    struct AntialiasingChangeEvent : public OptionChangeEvent {
        bool new_value;
    };

    struct ScreenResizeEvent : public OptionChangeEvent {
        glm::u32vec2 new_screen_dimensions;
    };

    using ScreenResizeEventHandler = core::EventHandler<ScreenResizeEvent>;
}
