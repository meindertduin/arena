#pragma once

#include "../graphics/render_target.h"

namespace editor {
    class WorldEditor {
    public:
        WorldEditor();
        void render();
    private:
        enum class Mode {
            Edit,
            Play,
            Pause,
        } m_mode { Mode::Edit };

        std::shared_ptr<graphics::RenderTarget> m_render_target;
    };
}