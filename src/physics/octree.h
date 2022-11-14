#pragma once

#include <array>
#include <vector>
#include "../math/box.h"
#include "physics_object.h"

#include <algorithm>

namespace physics {

    class OctreeNode {
    public:
        OctreeNode(float half_size, const glm::vec3 & center_pos);

        [[nodiscard]] constexpr bool inside(const math::AABB &other) const {
            return m_aabb.inside(other);
        }

        [[nodiscard]] bool inside_all(const math::AABB &other) const {
            if (m_count > 0) {
                return std::ranges::all_of(m_children.begin(), m_children.end(), [&other](auto child) {
                    return child->inside(other);
                });
            }

            return true;
        }

        void fill_inside_nodes(const math::AABB &aabb, std::vector<OctreeNode*> nodes) {
            if (inside_all(aabb)) {
                nodes.push_back(this);
                return;
            }

            for (auto child : m_children) {
                child->fill_inside_nodes(aabb, nodes);
            }
        }

        void reset() {
            m_values.clear();
            for (auto child : m_children) {
                child->reset();
            }
        }

        void add_child(OctreeNode *node) {
            m_children[m_count++] = node;
        }

        constexpr void add_value(PhysicsObject* value) {
            m_values.push_back(value);
            auto &aabb = value->rigid_body()->collider()->aabb();
            for (auto child : m_children) {
                if (child->inside(aabb)) {
                    child->add_value(value);
                }
            }
        }

        constexpr auto begin() { return m_children.begin(); }
        constexpr auto end() { return m_children.end(); }

        constexpr ALWAYS_INLINE std::vector<PhysicsObject*> values() { return m_values; }
    private:
        std::vector<PhysicsObject*> m_values;
        math::AABB m_aabb;
        std::array<OctreeNode*, 8> m_children;
        int m_count {0};
    };

    class Octree {
    public:
        Octree(float half_size, int max_layers);

        std::vector<OctreeNode *> get_colliding_nodes(PhysicsObject *object);
        void fill_with_objects(const std::vector<PhysicsObject*>& physics_objects);
        void reset();
    private:
        OctreeNode* m_root;
        int m_max_layers;

        void add_node_layers(OctreeNode *node, const glm::vec3 &center, float half_size, int layer) const;
    };
}