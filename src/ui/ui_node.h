#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "component.h"

namespace ui {
    struct UIMouseClickEvent {
        int button;
        glm::ivec2 mouse_pos;
    };

    class UINode {
    public:
        int id;
        std::unique_ptr<UIComponent> component;

        void render();
        void add_child(UINode &&node);

        bool on_click(const UIMouseClickEvent &event);
    private:
        std::vector<UINode> children;
        UINode *parent {nullptr};
    };
}
