#include "component.h"
#include "../global.h"
#include "ui.h"
#include "element_builder.h"

namespace ui {
    void UiElement::handle_event(UIEventType type, UIEvent *event) {
        if (!display) {
            parent->handle_event(type, event);
        }

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

    ButtonComponent::ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size, const std::string& text, std::function<void(UIEvent *)> &&on_click)
            : Component(pos, size), text{text}, on_click{on_click} { }

    void ButtonComponent::build(View &view, UiElement *binding_element) {
        view.create_element<UiElement>([&](ElementBuilder<UiElement> &builder) {
            builder.add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 1, 0, 0, 1}, glm::vec4 { 1, 1, 1, 1 }, 2)
                .add_attribute<GeometryAttribute>(AttributeType::GeometryHovered, glm::vec4 { 0, 0, 1, 1}, glm::vec4 { 1, 1, 1, 1 }, 2)
                .add_attribute<TextAttribute>(AttributeType::Text, text, 20, true)
                .add_event_handler({ UIEventType::MouseButton, on_click });
        }, binding_element, pos, size);
    }

    DrawerComponent::DrawerComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : Component(pos, size) {
        expanded_size = { size.x, size.y };
    }

    void DrawerComponent::build(View &view, UiElement *binding_element) {
        items_container_id = view.create_element<UiElement>([](ElementBuilder<UiElement> &builder){
            builder.add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 1, 0, 0, 1}, glm::vec4 { 1, 0, 0, 1 }, 2)
                .with_display(false);
        } ,binding_element, glm::ivec2 { pos.x, pos.y + size.y }, folded_size);

        auto items_container = view.get_element(items_container_id);
        button = std::make_unique<ButtonComponent>(pos, size, "Click me!", [&, items_container](auto event) {
            if (expanded) {
                items_container->size = this->folded_size;
                items_container->display = false;
            } else {
                items_container->size = this->expanded_size;
                items_container->display = true;
            }

            expanded = !expanded;
        });

        button->build(view, binding_element);

        int prev_height = folded_size.y;
        for (auto &item : items) {
            item->pos = { 0, prev_height };
            item->build(view, items_container);
            prev_height += item->size.y;
        }
    }

    void DrawerComponent::add_item(std::unique_ptr<Component> &&component) {
        expanded_size.y += component->size.y;
        items.push_back(std::forward<std::unique_ptr<Component>>(component));
    }
}