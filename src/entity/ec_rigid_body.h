#pragma once

#include "component.h"
#include "../graphics/mesh.h"
#include "ec_collision_object.h"

namespace entity {
    class ECRigidBody : public ECCollisionObject {
    public:
        glm::vec3 velocity;
        glm::vec3 force;
        float mass { 50 };

        explicit ECRigidBody(bool is_dynamic, ECTransform *transform) :
            ECCollisionObject(is_dynamic, transform)
        {}

        ECRigidBody(bool detect_collisions, bool is_dynamic, ECTransform *transform) :
            ECCollisionObject(detect_collisions ,is_dynamic, transform)
        {}
    private:
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

