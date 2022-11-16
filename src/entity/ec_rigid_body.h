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

        explicit ECRigidBody(bool is_dynamic) :
            ECCollisionObject(is_dynamic)
        {}

        ECRigidBody(bool detect_collisions, bool is_dynamic)
            : ECCollisionObject(detect_collisions, is_dynamic) {}
    private:
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

