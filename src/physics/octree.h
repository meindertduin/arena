#pragma once

#include <array>
#include <vector>
#include "../math/box.h"
#include "physics_object.h"

#include <algorithm>

namespace physics {
    class Octree {
    private:
        class OctreeNode;
    public:
        Octree(float half_size, int max_layers);

        std::set<PhysicsObject*> get_colliding_objects(const PhysicsObject &object);
        void fill_with_objects(const std::vector<PhysicsObject*>& physics_objects);
        void reset();
    private:
        OctreeNode* m_root;
        int m_max_layers;
        float m_half_size;
        float m_grid_size;

        void add_node_layers(OctreeNode *node, const glm::vec3 &center, float half_size, int layer) const;
        static int get_max_layer(float smallest_half, int max_layer, float grid_size);
        std::vector<OctreeNode *> get_colliding_nodes(const PhysicsObject &object);

    private:
        class OctreeNode {
        public:
            OctreeNode(float half_size, const glm::vec3 & center_pos, int layer);

            [[nodiscard]] bool inside(const math::AABB &other) const {
                return m_aabb.inside(other);
            }

            void get_inside_nodes(const math::AABB &aabb, std::vector<OctreeNode*> &nodes, int max_layer);

            void reset();

            void add_child(OctreeNode *node);

            void add_value(PhysicsObject* value, const math::AABB &aabb);

            constexpr auto begin() { return m_children.begin(); }
            constexpr auto end() { return m_children.end(); }

            constexpr ALWAYS_INLINE std::vector<PhysicsObject*> values() { return m_values; }
        private:
            std::vector<PhysicsObject*> m_values;
            math::AABB m_aabb;
            std::array<OctreeNode*, 8> m_children{};

            int m_count {0};
            int m_layer{0};
        };
    };
}