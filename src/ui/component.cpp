#include "component.h"
#include "../global.h"
#include "ui.h"

namespace ui {
    void UiElement::handle_event(UIEventType type, UIEvent *event) {
        if (event_handlers.find(type) != event_handlers.end()) {
            event_handlers[type](event);
        }

        if (event->stop_bubbling) {
            return;
        }

        if (parent != nullptr)
            parent->handle_event(type, event);
    }

    TextElement::TextElement(const glm::ivec2 &pos, const glm::ivec2 &size, const std::string &text) : UiElement(pos, size) {
        attributes.insert({ AttributeType::Text, std::make_unique<TextAttribute>(text)});

        event_handlers.insert({ UIEventType::MouseMove, [&](UIEvent *event) {
            event->stop_bubbling = true;
            this->is_hovered = true;
        }});
    }

    FrameTimeCounter::FrameTimeCounter(const glm::ivec2 &pos, const glm::ivec2 &size) : UiElement(pos, size) {
        auto text = get_frame_time_string();
        attributes.insert({ AttributeType::Text, std::make_unique<TextAttribute>(text) });
    }

    void FrameTimeCounter::on_tick(uint64_t tick) {
        auto text_attribute = get_attribute<TextAttribute>(AttributeType::Text);
        text_attribute->text = get_frame_time_string();
    }

    std::string FrameTimeCounter::get_frame_time_string() {
        return "Frame time: " + std::to_string(global.telemetrics.last_frame_time_ms) + "ms";
    }
}