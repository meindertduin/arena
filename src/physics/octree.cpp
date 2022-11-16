#include "octree.h"

#include "collision.h"
#include "../entity/ec_collision_object.h"

namespace physics {
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

    void Octree::fill_with_objects(const std::vector<entity::Entity>& entities) {
        for (auto object : entities) {
            // TODO, decide some place else when objects get added
            auto &collision_object = object.get<entity::ECCollisionObject>();
            auto &transform = object.get<entity::ECTransform>();

            auto aabb = collision_object.collider()->aabb().transformed(transform.pos);

            m_root->add_value(object, aabb);
        }
    }

    std::vector<Octree::OctreeNode*> Octree::get_colliding_nodes(entity::Entity entity) {
        std::vector<OctreeNode*> nodes;
        auto &collision_object = entity.get<entity::ECRigidBody>();
        auto &transform = entity.get<entity::ECTransform>();

        auto aabb = collision_object.collider()->aabb()
                .transformed(transform.pos);

        if (!m_root->inside(aabb)) {
            return nodes;
        }

        float smallest_side = aabb.smallest_side();

        auto max_layer = get_max_layer(smallest_side, m_max_layers, m_grid_size);
        m_root->get_inside_nodes(aabb, nodes, max_layer);

        return nodes;
    }

    std::set<entity::Entity> Octree::get_colliding_objects(entity::Entity object) {
        std::set<entity::Entity> colliding_objects;
        auto colliding_nodes = get_colliding_nodes(object);
        for (auto node : colliding_nodes) {
            for (auto value : node->values()) {
                if (object == value) {
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

    Octree::OctreeNode::OctreeNode(float half_size, const glm::vec3 &center_pos, int layer) : m_layer{layer}{
        auto min = glm::vec3{ center_pos.x - half_size, center_pos.y - half_size, center_pos.z - half_size };
        auto max = glm::vec3{ center_pos.x + half_size, center_pos.y + half_size, center_pos.z + half_size };

        m_aabb = math::AABB { min, max };
    }

    void Octree::OctreeNode::get_inside_nodes(const math::AABB &aabb, std::vector<OctreeNode *> &nodes, int max_layer) {
        if (!m_aabb.inside(aabb)) {
            return;
        }

        if ((m_layer + 1) >= max_layer) {
            nodes.push_back(this);
            return;
        }

        for (auto child : m_children) {
            child->get_inside_nodes(aabb, nodes, max_layer);
        }
    }

    void Octree::OctreeNode::reset() {
        if (m_values.empty()) {
            return;
        }

        m_values.clear();
        for (auto child : m_children) {
            if (child == nullptr) {
                break;
            }

            child->reset();
        }
    }

    void Octree::OctreeNode::add_child(Octree::OctreeNode *node) {
        m_children[m_count++] = node;
    }

    void Octree::OctreeNode::add_value(entity::Entity entity, const math::AABB &aabb) {
        m_values.push_back(entity);
        for (auto child : m_children) {
            if (child == nullptr) {
                break;
            }

            if (child->inside(aabb)) {
                child->add_value(entity, aabb);
            }
        }
    }
}