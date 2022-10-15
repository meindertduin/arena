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
        dispatcher->emit_event(event);
    }

    void GraphicOptions::set_size(const U32Size &size) {
        if (size == m_size)
            return;

        auto dispatcher = core::EventDispatcher<ScreenResizeEvent>::instance();
        ScreenResizeEvent event{};

        event.event_type = core::Event::EventType::SettingChangeEvent;
        event.option_type = OptionChangeEvent::OptionType::ScreenResize;
        event.new_size = size;
        dispatcher->emit_event(event);

        m_size = size;
    }
}
