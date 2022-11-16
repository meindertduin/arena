#include "ec_collision_object.h"
#include "../physics/collision.h"

namespace entity {
    physics::CollisionPoints ECCollisionObject::test_collision(ECCollisionObject &other) {
        return m_collider->test_collision(transform(), other.collider().get(), other.transform());
    }
}