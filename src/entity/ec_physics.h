#pragma once
#include "component.h"

namespace entity {
    class ECPhysics : public Component<ECPhysics> {
    public:
        glm::vec3 velocity;
        glm::vec3 force;
        float mass { 50 };
    };

    DECL_COMPONENT_HEADER(ECPhysics);
}