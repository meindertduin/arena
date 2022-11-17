#pragma once

#include "component.h"
#include "../graphics/mesh.h"
#include "ec_collision_object.h"

namespace entity {
    class ECRigidBody : public CollisionObject, public Component<ECRigidBody> {
    public:
        glm::vec3 velocity { 0 };
        glm::vec3 force { 0 };
        float mass { 50 };

        explicit ECRigidBody(bool is_dynamic) :
            CollisionObject(is_dynamic),
            Component<ECRigidBody>()
        {
            mp_transform = entity.get_ptr<ECTransform>();
        }

        ECRigidBody(bool detect_collisions, bool is_dynamic)
            : CollisionObject(detect_collisions, is_dynamic),
              Component<ECRigidBody>()
        {
            mp_transform = entity.get_ptr<ECTransform>();
        }

        [[nodiscard]] physics::CollisionPoints test_collision(const ECCollisionObject &other);
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

