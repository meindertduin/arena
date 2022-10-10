#pragma once

#include "component.h"

#include "../input/input.h"
#include <array>

namespace ui {
    struct UIEvent {
        bool stop_bubbling { false };
    };

    struct UIMouseClickEvent : public UIEvent {
        uint32_t button;
        glm::ivec2 mouse_pos;
    };

    struct UIMouseMoveEvent : public UIEvent {
        glm::ivec2 mouse_pos;
    };

    class UI {
    public:
        UI();
        std::unique_ptr<UiElement> root;

        void handle_mouse_move_event();
        void handle_mouse_button_event(const input::KeyCombination &combi);
        void handle_key_event(const input::KeyCombination &combi);
        void render();
        void on_tick(uint64_t tick);

        void open_dev_info();
        void open_edit_tools();
    private:
        bool on_mouse_move(UiElement *element, UIMouseMoveEvent &event);
        bool on_click(UiElement *element, UIMouseClickEvent &event) const;
        void handle_element_ticks(uint64_t tick, std::unique_ptr<UiElement> &element);
    };
}