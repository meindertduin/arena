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

    FrameTimeCounter::FrameTimeCounter(const glm::ivec2 &pos, const glm::ivec2 &size, int text_size) : UiElement(pos, size) {
        auto text = get_frame_time_string();
        auto text_attribute = std::make_unique<TextAttribute>(text);
        text_attribute->text_size = text_size;
        if (size.y < text_size) {
            this->size.y = text_size;
        }
        attributes.insert({ AttributeType::Text, std::move(text_attribute) });
    }

    void FrameTimeCounter::on_tick(uint64_t tick) {
        auto text_attribute = get_attribute<TextAttribute>(AttributeType::Text);
        text_attribute->text = get_frame_time_string();
    }

    std::string FrameTimeCounter::get_frame_time_string() {
        return "Frame time: " + std::to_string(global.telemetrics.last_frame_time_ms) + "ms";
    }

    Button::Button(const glm::ivec2 &pos, const glm::ivec2 &size, std::string text, std::function<void(UIEvent*)>&& on_click)
        : UiElement(pos, size) {
        this->event_handlers.insert({ UIEventType::MouseButton, std::forward<std::function<void(UIEvent*)>>(on_click) });
        add_attribute<TextAttribute>(AttributeType::Text, text, 20, true);
    }

    DrawerComponent::DrawerComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : Component(pos, size), folded_size{size} {
        expanded_size = { size.x, size.y * 2 };
    }

    void DrawerComponent::build(View &view, UiElement *binding_element) {
        background_id = view.add_element(binding_element, std::make_unique<UiElement>(pos, size));
        auto background = view.get_element(background_id);

        button = std::make_unique<ButtonComponent>(pos, folded_size, "Click me!", [=](auto event) {
            if (expanded) {
                background->size = this->folded_size;
            } else {
                background->size = this->expanded_size;
            }

            expanded = !expanded;
        });

        button->build(view, background);
        background->add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 1, 0, 0, 1}, glm::vec4 { 1, 0, 0, 1 }, 2);
    }

    ButtonComponent::ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size, const std::string& text, std::function<void(UIEvent *)> &&on_click)
        : Component(pos, size), text{text}, on_click{on_click} { }

    void ButtonComponent::build(View &view, UiElement *binding_element) {
        background_id = view.add_element(binding_element, std::make_unique<UiElement>(pos, size));
        auto background = view.get_element(background_id);

        background->event_handlers.insert({ UIEventType::MouseButton, on_click });
        background->add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 1, 0, 0, 1}, glm::vec4 { 1, 1, 1, 1 }, 2);
        background->add_attribute<GeometryAttribute>(AttributeType::GeometryHovered, glm::vec4 { 0, 0, 1, 1}, glm::vec4 { 1, 1, 1, 1 }, 2);
        background->add_attribute<TextAttribute>(AttributeType::Text, text, 20, true);
    }
}