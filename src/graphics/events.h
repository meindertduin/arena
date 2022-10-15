#pragma once

#include <glm/glm.hpp>

#include "../core/event.h"
#include "../core/event_dispatcher.h"
#include "rect.h"

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
        U32Size new_size;
    };

    using ScreenResizeEventHandler = core::EventHandler<ScreenResizeEvent>;
}
