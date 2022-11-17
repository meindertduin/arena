#include "solver.h"

namespace physics {
    void PositionSolver::solve(const std::vector<Collision> &collisions, float dt) {
        for (auto &collision : collisions) {
            int a_static = (int) collision.collision_object_a->is_static();
            int b_static = (int) collision.collision_object_b->is_static();

            auto transform_a = collision.collision_object_a->transform();
            auto transform_b = collision.collision_object_b->transform();

            auto resolution = collision.points.normal * (collision.points.depth / std::max(1, a_static + b_static));
            if (!a_static)
                transform_a->move(-resolution);
            if (!b_static)
                transform_b->move(resolution);
        }
    }
}