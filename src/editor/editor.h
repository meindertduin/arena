#pragma once

#include "world_editor.h"

namespace editor {
    class Editor  {
    public:
        void initialize();
        void update();
    private:
        WorldEditor m_world_editor;
        bool my_tool_active = false;
    };
}