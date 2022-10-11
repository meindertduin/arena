#include "view.h"

#include "../global.h"
#include "../graphics/ui_renderer.h"

namespace ui {
    inline static bool on_mouse_move(UiElement *component, UIMouseMoveEvent &event);
    inline static bool on_click(UiElement *component, UIMouseClickEvent &event);

    View::View() {
        root_element = std::make_unique<RootElement>(glm::ivec2 { 0, 0 }, glm::ivec2 {  global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y });
        root_element->add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 0.1f, 0.1f, 0.1f, 0.25f });

        auto component = std::make_unique<DrawerComponent>(glm::ivec2 { 100, 100}, glm::ivec2 { 200, 40 });
        component->build(*this, root_element.get());
        components.push_back(std::move(component));

        auto info = std::make_unique<FrameTimeCounter>(glm::ivec2 { 10, 10}, glm::ivec2 { 200, 40 }, 20);
        info->get_attribute<TextAttribute>(AttributeType::Text)->center_text = true;
        info->add_attribute<GeometryAttribute>(AttributeType::Geometry, glm::vec4 { 1, 0, 0, 1 });

        add_element(root_element.get(), std::move(info));
    }

    void View::render() {
        global.ui_renderer->render(root_element.get());
    }

    void View::on_tick(uint64_t tick) {
        handle_element_ticks(tick, root_element);
    }

    void View::handle_element_ticks(uint64_t tick, std::unique_ptr<UiElement> &element) {
        element->on_tick(tick);
        for (auto &child : element->children) {
            handle_element_ticks(tick, child);
        }
    }

    void View::handle_mouse_click(UIMouseClickEvent &event) {
        on_click(root_element.get(), event);
    }

    void View::handle_mouse_move(UIMouseMoveEvent &event) {
        on_mouse_move(root_element.get(), event);
    }

    uint32_t View::add_element(UiElement *parent, std::unique_ptr<UiElement> &&element) {
        auto element_ptr = element.get();
        elements.push_back(element_ptr);

        element->parent = parent;
        parent->children.push_back(std::forward<std::unique_ptr<UiElement>>(element));

        return elements_count++;
    }

    uint32_t View::add_element(uint32_t parent_id, std::unique_ptr<UiElement> &&element) {
        auto parent = elements[parent_id];
        if (parent == nullptr) {
            THROW_ERROR("UI: Element with id: %id does not exist.", std::to_string(parent_id));
        }

        return add_element(parent, std::forward<std::unique_ptr<UiElement>>(element));
    }

    bool on_mouse_move(UiElement *component, UIMouseMoveEvent &event) {
        auto &component_ref = *component;

        component_ref.is_hovered = false;
        bool hovers_element;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            component_ref.is_hovered = true;
            hovers_element = true;
        }

        if (!hovers_element) {
            return false;
        }

        bool hovers_child;
        for (auto &child : component_ref.children) {
            hovers_child = on_mouse_move(child.get(), event);
        }

        // We want to fire the event only at the deepest, because the event will be bubbled up
        if (!hovers_child) {
            component_ref.handle_event(UIEventType::MouseMove, &event);
        }

        return true;
    }

    bool on_click(UiElement *component, UIMouseClickEvent &event) {
        auto &component_ref = *component;

        bool clicks_component = false;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            clicks_component = true;
        }

        if (!clicks_component) {
            return false;
        }

        bool clicks_child = false;
        for (auto &child : component_ref.children) {
            clicks_child = on_click(child.get(), event);
        }

        if (!clicks_child) {
            component_ref.handle_event(UIEventType::MouseButton, &event);
        }

        return true;
    }
}
