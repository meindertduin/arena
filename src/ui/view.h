#include "component.h"

#include "events.h"

#include "element_builder.h"

namespace ui {
    class View {
    public:
        // TODO read xml from file
        View();

        void render();
        void on_tick(uint64_t tick);

        template<typename T, typename ...Args>
        uint32_t create_element(std::function<void(ElementBuilder<T>&)> builder_callback, UiElement* parent, const glm::ivec2 &pos, Args&&... args) {
            auto builder = ElementBuilder<T>::get( parent, pos, std::forward<Args>(args)...);
            builder_callback(builder);

            auto element = builder.build();
            elements.push_back(element.get());
            parent->children.push_back(std::move(element));

            return elements_count++;
        }

        template<typename T, typename ...Args>
        uint32_t create_element(UiElement* parent, const glm::ivec2 &pos, Args&&... args) {
            auto element = ElementBuilder<T>::get( parent, pos, std::forward<Args>(args)...).build();

            elements.push_back(element.get());
            parent->children.push_back(std::move(element));

            return elements_count++;
        }

        uint32_t add_element(UiElement* parent, std::unique_ptr<UiElement> &&element);
        uint32_t add_element(uint32_t parent_id, std::unique_ptr<UiElement> &&element);

        UiElement* get_element(uint32_t id);

        void handle_mouse_click(UIMouseClickEvent &event);
        void handle_mouse_move(UIMouseMoveEvent &event);
    private:
        std::unique_ptr<UiElement> root_element;
        std::vector<UiElement*> elements;
        uint32_t elements_count { 0 };

        std::vector<std::unique_ptr<Component>> components;

        static void handle_element_ticks(uint64_t tick, std::unique_ptr<UiElement> &element);
    };
}
