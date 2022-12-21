#pragma once

#include <vector>
#include <string>

namespace editor {
    struct Node {
        int depth { 0 };
        bool open { false };
        bool selected { false };
        bool leaf { false };

        std::string label;

        Node* parent { nullptr };
        std::vector<Node*> children;

        Node* add_child(Node* child, const std::string &child_label) {
            child->parent = this;
            child->depth = depth + 1;
            child->label = child_label;
            child->leaf = true;

            children.push_back(child);
            leaf = false;

            return child;
        }
    };

    class SceneView {
    public:
        SceneView();
        void render();
    private:
        Node *m_root;

        void render_node(Node *node);
    };
}
