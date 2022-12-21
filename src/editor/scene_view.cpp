#include "scene_view.h"
#include "imgui/imgui.h"

namespace editor {
    void SceneView::render() {
        static bool selected = false;
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        {
            ImGui::SetWindowSize(ImVec2(200, 400));
            if (ImGui::Selectable("Camera", selected)) {
                selected = true;
            }
        }
        ImGui::End();
    }
}