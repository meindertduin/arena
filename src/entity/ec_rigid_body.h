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
            CollisionObject(is_dynamic)
        {}

        ECRigidBody(bool detect_collisions, bool is_dynamic)
            : CollisionObject(detect_collisions, is_dynamic) {}

        [[nodiscard]] physics::CollisionPoints test_collision(const ECCollisionObject &other);
    private:
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

