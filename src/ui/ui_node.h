#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace ui {
    class UINode {
    public:
        int id;
        int width;
        int height;

        glm::ivec2 pos;
    private:
        std::vector<std::unique_ptr<UINode>> children;
        std::weak_ptr<UINode> parent;
    };
}
