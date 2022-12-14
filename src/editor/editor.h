#pragma once

namespace editor {
    class Editor  {
    public:
        void initialize();
        void update();
    private:
        bool my_tool_active = false;
    };
}