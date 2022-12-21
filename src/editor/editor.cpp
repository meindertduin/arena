#include "editor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

namespace editor {
    void Editor::initialize() {
        // setup settings
    }

    void Editor::update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render the world editor
        m_world_editor.render();
        m_scene_view.render();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
}
