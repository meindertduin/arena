#include "ec_collision_object.h"
#include "../physics/collision.h"

namespace entity {
    physics::CollisionPoints ECCollisionObject::test_collision(const ECCollisionObject &other) {
        auto &transform = entity.get<ECTransform>();
        auto &other_transform = other.entity.get<ECTransform>();

        return collider()->test_collision(transform, other.collider().get(), other_transform);
    }
}