#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>

#include "../math/box.h"
#include "../entity/entity.h"

namespace physics {
    template<typename T>
    class OctreeNode {
    public:
        OctreeNode(float half_size, const glm::vec3 &center_pos, int layer) : m_layer{layer}{
            auto min = glm::vec3{ center_pos.x - half_size, center_pos.y - half_size, center_pos.z - half_size };
            auto max = glm::vec3{ center_pos.x + half_size, center_pos.y + half_size, center_pos.z + half_size };

            m_aabb = math::AABB { min, max };
        }

        [[nodiscard]] bool inside(const math::AABB &other) const {
            return m_aabb.inside(other);
        }

        void get_inside_nodes(const math::AABB &aabb, std::vector<OctreeNode*> &nodes, int max_layer) {
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

        void reset() {
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

        void add_child(OctreeNode *node) {
            m_children[m_count++] = node;
        }

        void add_value(entity::Entity entity, const math::AABB &aabb) {
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

        constexpr auto begin() { return m_children.begin(); }
        constexpr auto end() { return m_children.end(); }

        constexpr ALWAYS_INLINE std::vector<T> values() { return m_values; }
    private:
        std::vector<T> m_values;
        math::AABB m_aabb;
        std::array<OctreeNode<T>*, 8> m_children{};

        int m_count {0};
        int m_layer{0};
    };
}