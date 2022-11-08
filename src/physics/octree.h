#pragma once

#include <array>
#include <vector>
#include "../math/box.h"

namespace physics {
    template<typename T>
    class OctreeNode {
    public:
        [[nodiscard]] bool inside(const math::AABB &other) const {
            return m_aabb.inside(other);
        }

        void add_child(OctreeNode<T> &&node) {
            m_children[m_count] = std::move(node);
        }

        void add_value(T* value) {
            m_values.push_back(value);
        }
    private:
        std::vector<T*> m_values;
        math::AABB m_aabb;
        std::array<OctreeNode<T>, 8> m_children;
        int m_count {0};
    };

    class Octree {
    public:

    };
}