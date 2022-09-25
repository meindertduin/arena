//
// Created by meindert on 9/25/22.
//

#include "ui_node.h"

namespace ui {
    void UINode::render() {
        component->render();
        for (auto &child : children)
            child.render();
    }

    void UINode::add_child(UINode &&node) {
        node.parent = this;
        children.push_back(std::move(node));
    }
}
