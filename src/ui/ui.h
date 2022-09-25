#pragma once

#include "ui_node.h"

class UI {
public:
    std::unique_ptr<ui::UINode> root;

    void handle_event();
    void render();
};
