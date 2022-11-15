#include "solver.h"
#include "physics_object.h"

namespace physics {
    void PositionSolver::solve(std::vector<Collision> &collisions, float dt) {
        for (auto &collision : collisions) {
            int a_static = (int) collision.physics_object_a->rigid_body()->is_static();
            int b_static = (int) collision.physics_object_b->rigid_body()->is_static();

            auto resolution = collision.points.normal * (collision.points.depth / std::max(1, a_static + b_static));
            if (!a_static)
                collision.physics_object_a->transform()->move(-resolution);
            if (!b_static)
                collision.physics_object_a->transform()->move(resolution);
        }
    }
}