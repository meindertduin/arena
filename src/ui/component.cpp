#include "component.h"
#include "../global.h"
#include "../graphics/renderer.h"
#include "component_builder.h"

namespace ui {
    RootComponent::RootComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
        // children.push_back(std::make_unique<ButtonComponent>(glm::ivec2{ 100, 100 }, glm::ivec2{ 130, 40 }));
    }

    PlaneComponent::PlaneComponent(const glm::ivec2 &pos, const glm::ivec2 &size) : UIComponent(pos, size) {
        // background.set_pos_and_size({ pos.x + 2, pos.y + 2 }, { size.x - 4, size.y - 4 });
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
        // global.ui_renderer->render(border, border_color);
        // if (is_hovered) {
        //     global.ui_renderer->render(background, { 0, 0, 1.0f, 1.0f });
        // } else {
        //     global.ui_renderer->render(background, background_color);
        // }

        // global.text_renderer->render(text, { gl_pos.x + 10, gl_pos.y + 10 }, text_size);

        UIComponent::render();
    }

    void ButtonComponent::handle_click(const UIMouseClickEvent &event) {
        printf("Element is clicked!\n");
    }
}