#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"
#include "component_builder.h"
#include "ui.h"

namespace ui {
    void UIComponent::handle_event(UIEventType type, UIEvent *event) {
        if (event_handlers.find(type) != event_handlers.end()) {
            event_handlers[type](event);
        }

        if (event->stop_bubbling) {
            return;
        }

        if (parent != nullptr)
            parent->handle_event(type, event);
    }

    RootComponent::RootComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
    }

    PlaneComponent::PlaneComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
        event_handlers.insert({UIEventType::MouseButton, [&](UIEvent *event) {
            event->stop_bubbling = true;
            background_color = { 0, 0, 1.0f, 1.0f };
        }});
    }

    void PlaneComponent::render() {
        global.ui_renderer->render(border, border_color);
        global.ui_renderer->render(background, background_color);
        UIComponent::render();
    }

    TextComponent::TextComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) { }

    void TextComponent::render() {
        global.text_renderer->render(text, { gl_pos.x, gl_pos.y }, text_size);
        UIComponent::render();
    }

    ButtonComponent::ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
        ComponentBuilder<PlaneComponent> builder;
        auto component = builder.with_parent(this)
            .with_rel_pos_and_size(glm::ivec2{ 0, 0 }, size)
            .with_background({ 0.15f, 0.15f, 0.15f, 1.0f })
            .with_border(2, { 1.0f, 1.0f, 1.0f, 1.0f })
            .with_child<TextComponent>([&](ComponentBuilder<TextComponent> &builder) {
                builder.with_rel_pos_and_size({ 0, 0 }, { size.x, size.y })
                    .with_text("Hello world!", 14);
            })
            .build();

        children.push_back(std::move(component));
    }

    void ButtonComponent::render() {
        UIComponent::render();
    }
}