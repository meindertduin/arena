#include "graphic_options.h"

#include "events.h"

namespace graphics {
    void GraphicOptions::set_antialiasing(bool new_value) {
        if (new_value == antialiasing)
            return;

        auto dispatcher = core::EventDispatcher<AntialiasingChangeEvent>::instance();
        AntialiasingChangeEvent event;

        event.event_type = core::Event::EventType::SettingChangeEvent;
        event.option_type = OptionChangeEvent::OptionType::Antialiasing;
        event.new_value = new_value;
        dispatcher->emitEvent(event);
    }

    void GraphicOptions::set_screen_dimensions(glm::u32vec2 new_value) {
        if (new_value == screen_dimensions)
            return;

        auto dispatcher = core::EventDispatcher<ScreenResizeEvent>::instance();
        ScreenResizeEvent event;

        event.event_type = core::Event::EventType::SettingChangeEvent;
        event.option_type = OptionChangeEvent::OptionType::ScreenResize;
        event.new_screen_dimensions = new_value;
        dispatcher->emitEvent(event);
    }

}
