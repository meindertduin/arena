#pragma once

#include "../graphics/render_target.h"

namespace editor {
    class WorldEditor {
    public:
        WorldEditor();
        void render();
    private:
        std::shared_ptr<graphics::RenderTarget> m_render_target;
    };
}