#pragma once

#include "simplex.h"
#include "collision.h"

namespace physics {
    std::pair<bool, Simplex> gjk(const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b);
    CollisionPoints epa(const Simplex &simplex,const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b);
}

