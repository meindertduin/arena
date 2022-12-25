#include "world_editor.h"
#include "../global.h"
#include "../graphics/renderer.h"
#include "imgui/imgui.h"

namespace editor {
    void WorldEditor::render() {
        switch (m_mode) {
            case Mode::Edit:
                break;
            case Mode::Play:
                break;
            case Mode::Pause:
                break;
        }

        ImGui::SetNextWindowPos(ImVec2(300, 20));
        ImGui::SetNextWindowSize(ImVec2(640, 480));
        ImGui::Begin("World Editor");
        {
            ImGui::BeginChild("GameRender");
            ImVec2 size = { 640, 480 };
            ImGui::Image((ImTextureID)m_render_target->get_screen_texture(), size, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
        }
        ImGui::End();

    }

    WorldEditor::WorldEditor()
        : m_render_target(std::make_shared<graphics::RenderTarget>())
    {
        global.application->renderer()->set_render_target(m_render_target);
    }
}

