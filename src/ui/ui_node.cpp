#include "ui_node.h"

namespace ui {
    void UINode::render() {
        if (component != nullptr)
            component->render();

        for (auto &child : children)
            child.render();
    }

    void UINode::add_child(UINode &&node) {
        node.parent = this;
        children.push_back(std::move(node));
    }
}
