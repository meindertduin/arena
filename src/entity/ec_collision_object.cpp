#include "ec_collision_object.h"
#include "../physics/collision.h"

namespace entity {
    physics::CollisionPoints ECCollisionObject::test_collision(const ECCollisionObject &other) {
        return m_collider->test_collision(*m_transform, other.collider().get(), *other.transform());
    }
}