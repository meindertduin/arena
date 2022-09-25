#pragma once

#include "ui_node.h"

namespace ui {
    class UI {
    public:
        UI();
        std::unique_ptr<ui::UINode> root;

        void handle_event();
        void render() const;
    };
}