#include "ui.h"

namespace ui {
    UI::UI() {
        auto node = new UINode{};
        node->component = std::make_unique<ButtonComponent>();
        root = std::unique_ptr<UINode>(node);
    }

    void UI::handle_event() {

    }

    void UI::render() const {
        root->render();
    }
}
