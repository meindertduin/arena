#pragma once

#include <array>
#include "../entity/entity.h"
#include "collision.h"
#include "../entity/ec_collision_object.h"
#include "octree_node.h"
#include <algorithm>
#include <set>
#include <concepts>

namespace physics {
    template<typename T>
    concept CollisionComponent = std::same_as<T, entity::ECCollisionObject> ||
                                 std::same_as<T, entity::ECRigidBody>;

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

    glm::vec3 create_octal_center(OctalPart part, const glm::vec3 &center, float quarter_size);

    class Octree {
    public:
        Octree(float half_size, int max_layers) :
                m_max_layers{max_layers},
                m_half_size{half_size},
                m_grid_size{half_size * (float) std::pow(0.5f, max_layers)}
        {
            auto center = glm::vec3 { 0 };
            m_root = new OctreeNode<entity::Entity> { half_size, center, 0 };

            auto quarter_size = half_size / 2.0f;
            add_node_layers(m_root, center, quarter_size, 1);
        }

        std::set<entity::Entity> get_colliding_objects(entity::Entity object) {
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

        void fill_with_objects(const std::vector<entity::Entity>& entities) {
            for (auto object : entities) {
                // TODO, decide some place else when objects get added
                auto &collision_object = object.get<entity::ECCollisionObject>();

                auto aabb = collision_object.collider()->aabb().transformed(collision_object.transform()->pos);

                m_root->add_value(object, aabb);
            }
        }

        void reset() {
            m_root->reset();
        }
    private:
        OctreeNode<entity::Entity>* m_root;
        int m_max_layers;
        float m_half_size;
        float m_grid_size;

        void add_node_layers(OctreeNode<entity::Entity> *node, const glm::vec3 &center, float half_size, int layer) const {
            if (layer >= m_max_layers) {
                return;
            }

            for (auto part = 0; part < 8; part++) {
                auto new_center = create_octal_center((OctalPart)part, center, half_size);
                auto new_node = new OctreeNode<entity::Entity> { half_size, new_center, layer };
                node->add_child(new_node);

                add_node_layers(new_node, new_center, half_size / 2.0f, layer + 1);
            }
        }

        static int get_max_layer(float smallest_half, int max_layer, float grid_size) {
            if (smallest_half > grid_size) {
                max_layer--;
                grid_size*= 2;
                get_max_layer(smallest_half, max_layer, grid_size);
            }

            return max_layer;
        }

        std::vector<OctreeNode<entity::Entity>*> get_colliding_nodes(entity::Entity entity) {
            std::vector<OctreeNode<entity::Entity>*> nodes;
            auto &collision_object = entity.get<entity::ECRigidBody>();

            auto aabb = collision_object.collider()->aabb()
                    .transformed(collision_object.transform()->pos);

            if (!m_root->inside(aabb)) {
                return nodes;
            }

            float smallest_side = aabb.smallest_side();

            auto max_layer = get_max_layer(smallest_side, m_max_layers, m_grid_size);
            m_root->get_inside_nodes(aabb, nodes, max_layer);

            return nodes;
        }
    };
}