#include "component.h"

#include "events.h"

namespace ui {
    class View {
    public:
        // TODO read xml from file
        View();

        void render();
        void on_tick(uint64_t tick);

        uint32_t add_element(UiElement* parent, std::unique_ptr<UiElement> &&element);
        uint32_t add_element(uint32_t parent_id, std::unique_ptr<UiElement> &&element);

        void handle_mouse_click(UIMouseClickEvent &event);
        void handle_mouse_move(UIMouseMoveEvent &event);
    private:
        std::unique_ptr<UiElement> root_element;
        std::vector<UiElement*> elements;
        uint32_t elements_count;

        std::vector<std::unique_ptr<Component>> components;

        static void handle_element_ticks(uint64_t tick, std::unique_ptr<UiElement> &element);
    };
}
