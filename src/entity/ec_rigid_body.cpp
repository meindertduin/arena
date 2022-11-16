#include "ec_rigid_body.h"
#include "../physics/collision.h"

namespace entity {
    physics::CollisionPoints ECRigidBody::test_collision(const ECCollisionObject &other) {
        auto &transform = entity.get<ECTransform>();
        auto &other_transform = other.entity.get<ECTransform>();

        return collider()->test_collision(transform, other.collider().get(), other_transform);
    }
}
