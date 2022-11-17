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

        explicit ECRigidBody(bool is_dynamic, ECTransform *transform) :
            CollisionObject(is_dynamic, transform),
            Component<ECRigidBody>()
        {}

        ECRigidBody(bool detect_collisions, bool is_dynamic, ECTransform *transform)
            : CollisionObject(detect_collisions, is_dynamic, transform),
              Component<ECRigidBody>()
        {}
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

