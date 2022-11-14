#include "physics_object.h"

namespace physics {

    CollisionPoints PhysicsObject::test_collision(const PhysicsObject &other) const {
        return m_rigid_body->collider()->
            test_collision(*m_transform, other.rigid_body()->collider().get(), *other.transform());
    }
}