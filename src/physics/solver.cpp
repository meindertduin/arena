#include "solver.h"

namespace physics {
    void PositionSolver::solve(std::vector<Collision> &collisions, float dt) {
        for (auto &collision : collisions) {
            int a_static = (int) collision.collision_object_a->is_static();
            int b_static = (int) collision.collision_object_b->is_static();

            auto resolution = collision.points.normal * (collision.points.depth / std::max(1, a_static + b_static));
            if (!a_static)
                collision.collision_object_a->transform().move(-resolution);
            if (!b_static)
                collision.collision_object_a->transform().move(resolution);
        }
    }
}