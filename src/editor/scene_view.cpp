#include <cstdint>
#include "scene_view.h"
#include "imgui/imgui.h"

namespace editor {
    SceneView::SceneView() {
        m_root = new Node();
        m_root->label = "Scene";

        auto child = m_root->add_child(new Node(), "Entity 1");
        child->add_child(new Node(), "Entity 1.1");
    }

    void SceneView::render() {
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        {
            ImGui::Button("+");

            if (ImGui::TreeNode(m_root->label.c_str()))
            {
                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

                if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                    open_popup(m_root);
                }

                for (auto & child : m_root->children)
                {
                    render_node(child);
                }

                ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());

                ImGui::TreePop();
            }
        }

        if (m_popup_opened) {
            ImGui::OpenPopup("Entity right click");
            m_popup_opened = false;
        }

        if (ImGui::BeginPopup("Entity right click"))
        {
            if (ImGui::Selectable("Add child")) {
                close_popup();
            }

            ImGui::EndPopup();
        }


        ImGui::End();
    }

    void SceneView::render_node(Node *node) {
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        ImGuiTreeNodeFlags node_flags = base_flags;

        if (node->leaf) {
            if (node->selected) {
                node_flags |= ImGuiTreeNodeFlags_Selected;
            }

            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

            ImGui::TreeNodeEx((void*)(intptr_t)1, node_flags, node->label.c_str());

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right))  {
                open_popup(node);
            } else if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                node->selected = !node->selected;
            }
        } else {
            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)1, node_flags, node->label.c_str());

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                open_popup(node);
            } else if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                node->selected = !node->selected;
            }

            if (node_open)
            {
                for (auto & child : node->children) {
                    render_node(child);
                }
                ImGui::TreePop();
            }
        }
    }

    void SceneView::open_popup(Node *node) {
        m_popup_opened = true;
        m_popup_node = node;
    }

    void SceneView::close_popup() {
        m_popup_node = nullptr;
        ImGui::CloseCurrentPopup();
    }
}