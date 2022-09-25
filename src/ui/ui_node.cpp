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

    bool UINode::on_click(const ui::UIMouseClickEvent &event) {
        auto &component_ref = *component;
        if (component_ref.pos.x <= event.mouse_pos.x && component_ref.pos.x + component_ref. size.x >= event.mouse_pos.x &&
            component_ref.pos.y <= event.mouse_pos.y && component_ref.pos.y + component_ref.size.y >= event.mouse_pos.y)
        {
            component_ref.handle_click(event);
            return true;
        }

        for (auto &child : children) {
            if (child.on_click(event))
                return true;
        }

        return false;
    }
}
