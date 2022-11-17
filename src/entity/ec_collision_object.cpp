#include "ec_collision_object.h"
#include "../physics/collision.h"

namespace entity {
    physics::CollisionPoints CollisionObject::test_collision(const CollisionObject *other) {
        return collider()->test_collision(*mp_transform, other->collider().get(), *other->transform());
    }
}