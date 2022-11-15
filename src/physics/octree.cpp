#include "octree.h"

namespace physics {
    OctreeNode::OctreeNode(float half_size, const glm::vec3 &center_pos, int layer) : m_layer{layer}{
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

    Octree::Octree(float half_size, int max_layers) :
        m_max_layers{max_layers},
        m_half_size{half_size},
        m_grid_size{half_size * (float) std::pow(0.5f, max_layers)}
    {
        auto center = glm::vec3 { 0 };
        m_root = new OctreeNode { half_size, center, 0 };

        auto quarter_size = half_size / 2.0f;
        add_node_layers(m_root, center, quarter_size, 1);
    }

    void Octree::fill_with_objects(const std::vector<PhysicsObject*> &physics_objects) {
        for (auto object : physics_objects) {
            m_root->add_value(object);
        }
    }

    std::vector<OctreeNode*> Octree::get_colliding_nodes(const PhysicsObject &object) {
        std::vector<OctreeNode*> nodes;
        auto &aabb = object.rigid_body()->collider()->aabb();

        if (!m_root->inside(aabb)) {
            return nodes;
        }

        float smallest_side = aabb.smallest_side();

        auto max_layer = get_max_layer(smallest_side, m_max_layers, m_grid_size);
        m_root->get_inside_nodes(aabb, nodes, max_layer);

        return nodes;
    }

    std::set<PhysicsObject*> Octree::get_colliding_objects(const PhysicsObject &object) {
        std::set<PhysicsObject*> colliding_objects;
        auto colliding_nodes = get_colliding_nodes(object);
        for (auto node : colliding_nodes) {
            for (auto value : node->values()) {
                if (object.entity() == value->entity()) {
                    continue;
                }

                colliding_objects.insert(value);
            }
        }

        return colliding_objects;
    }

    int Octree::get_max_layer(float smallest_half, int max_layer, float grid_size) {
        if (smallest_half > grid_size) {
            max_layer--;
            grid_size*= 2;
            get_max_layer(smallest_half, max_layer, grid_size);
        }

        return max_layer;
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
            auto new_node = new OctreeNode { half_size, new_center, layer };
            node->add_child(new_node);

            add_node_layers(new_node, new_center, half_size / 2.0f, layer + 1);
        }
    }
}