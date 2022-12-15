#include "world_editor.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace editor {
    void WorldEditor::render() {

    }

    WorldEditor::WorldEditor()
        : m_render_target(global.renderer->render_target())
    {
    }
}

