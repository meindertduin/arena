#include "solver.h"

#include "../entity/ec_collision.h"

namespace physics {
    void PositionSolver::solve(std::vector<Collision> &collisions, float dt) {
        for (auto &collision : collisions) {
            auto &collision_a = collision.entity_a.get<entity::ECCollision>();
            auto &collision_b = collision.entity_b.get<entity::ECCollision>();

            int a_static = (int) collision_a.is_static();
            int b_static = (int) collision_b.is_static();

            auto resolution = collision.points.normal * (collision.points.depth / std::max(1, a_static + b_static));
            if (!a_static)
                collision.transform_a.move(-resolution);
            if (!b_static)
                collision.transform_a.move(resolution);
        }
    }
}