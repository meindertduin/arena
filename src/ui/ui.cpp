#include "ui.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace ui {
    UI::UI() {
        auto node = new UINode{};
        node->component = std::make_unique<ButtonComponent>();
        root = std::unique_ptr<UINode>(node);
    }

    void UI::handle_event() {

    }

    void UI::render() const {
        global.ui_renderer->before_ui_rendering();
        root->render();
        global.ui_renderer->after_ui_rendering();
    }
}
