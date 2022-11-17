#pragma once

#include <array>
#include "../entity/entity.h"
#include "collision.h"
#include "../entity/ec_collision_object.h"
#include "octree_node.h"
#include <algorithm>
#include <set>

namespace physics {

    class Octree {
    public:
        Octree(float half_size, int max_layers);

        std::set<entity::Entity> get_colliding_objects(entity::Entity object);
        void fill_with_objects(const std::vector<entity::Entity>& entities);
        void reset();
    private:
        OctreeNode<entity::Entity>* m_root;
        int m_max_layers;
        float m_half_size;
        float m_grid_size;

        void add_node_layers(OctreeNode<entity::Entity> *node, const glm::vec3 &center, float half_size, int layer) const;
        static int get_max_layer(float smallest_half, int max_layer, float grid_size);
        std::vector<OctreeNode<entity::Entity>*> get_colliding_nodes(entity::Entity entity);
    };
}