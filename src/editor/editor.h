#pragma once

#include "world_editor.h"
#include "scene_view.h"

namespace editor {
    class Editor  {
    public:
        void initialize();
        void update();
    private:
        WorldEditor m_world_editor;
        SceneView m_scene_view;

        bool my_tool_active = false;
    };
}