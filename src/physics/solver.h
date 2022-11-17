#pragma once
#include "collision.h"

namespace physics {
    class Solver {
    public:
        virtual void solve(const std::vector<Collision> &collisions, float dt) = 0;
    };

    class PositionSolver : public Solver {
    public:
        void solve(const std::vector<Collision> &collisions, float dt) override;
    };
}
