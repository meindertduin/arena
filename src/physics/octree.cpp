#include "octree.h"

namespace physics {
    OctreeNode::OctreeNode(float half_size, const glm::vec3 &center_pos) {
        auto min = glm::vec3{ center_pos.x - half_size, center_pos.y - half_size, center_pos.z - half_size };
        auto max = glm::vec3{ center_pos.x + half_size, center_pos.y + half_size, center_pos.z + half_size };

        m_aabb = math::AABB { min, max };
    }

    enum OctalPart {
        LeftUpperFurthest = 0,
        RightUpperFurthest = 1,
        LeftLowerFurthest = 2,
        RightLowerFurthest = 3,
        LeftUpperClosest = 4,
        RightUpperClosest = 5,
        LeftLowerClosest = 6,
        RightLowerClosest = 7,
    };

    glm::vec3 create_octal_center(OctalPart part, const glm::vec3 &center, float quarter_size) {
        switch (part) {
            case LeftUpperFurthest:
                return { center.x - quarter_size, center.y + quarter_size, center.z + quarter_size };
            case RightUpperFurthest:
                return { center.x + quarter_size, center.y + quarter_size, center.z + quarter_size };
            case LeftLowerFurthest:
                return { center.x - quarter_size, center.y - quarter_size, center.z + quarter_size };
            case RightLowerFurthest:
                return { center.x + quarter_size, center.y - quarter_size, center.z + quarter_size };
            case LeftUpperClosest:
                return { center.x - quarter_size, center.y + quarter_size, center.z - quarter_size };
            case RightUpperClosest:
                return { center.x + quarter_size, center.y + quarter_size, center.z - quarter_size };
            case LeftLowerClosest:
                return { center.x - quarter_size, center.y - quarter_size, center.z - quarter_size };
            case RightLowerClosest:
                return { center.x + quarter_size, center.y - quarter_size, center.z - quarter_size };
        }
    }

    Octree::Octree(float half_size, int max_layers) : m_max_layers{max_layers} {
        auto center = glm::vec3 { 0 };
        m_root = new OctreeNode { half_size, center };

        auto quarter_size = half_size / 2.0f;
        add_node_layers(m_root, center, quarter_size, 0);
    }

    void Octree::fill_with_objects(const std::vector<PhysicsObject*> &physics_objects) {
        for (auto object : physics_objects) {
            m_root->add_value(object);
        }
    }

    std::vector<OctreeNode*> Octree::get_colliding_nodes(PhysicsObject *object) {
        auto &aabb = object->rigid_body()->collider()->aabb();
        std::vector<OctreeNode*> nodes;

        if (!m_root->inside(aabb)) {
            return nodes;
        }

        for (auto root_child : *m_root) {
            root_child->fill_inside_nodes(aabb, nodes);
        }

        return nodes;
    }

    void Octree::reset() {
        m_root->reset();
    }

    void Octree::add_node_layers(OctreeNode *node, const glm::vec3 &center, float half_size, int layer) const {
        if (layer >= m_max_layers) {
            return;
        }

        for (auto part = 0; part < 8; part++) {
            auto new_center = create_octal_center((OctalPart)part, center, half_size);
            auto new_node = new OctreeNode { half_size, new_center };
            node->add_child(new_node);

            add_node_layers(new_node, new_center, half_size / 2.0f, layer + 1);
        }
    }
}