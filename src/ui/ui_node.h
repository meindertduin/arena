#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "component.h"

namespace ui {
    class UINode {
    public:
        int id;
        glm::ivec2 pos;
        std::unique_ptr<UIComponent> component;

        void render();
        void add_child(UINode &&node);
    private:
        std::vector<UINode> children;
        UINode *parent {nullptr};
    };
}
