#pragma once

#include <glm/vec3.hpp>
#include "../entity/system.h"
#include "octree.h"

namespace physics {
    class PhysicsSystem : public entity::System {
    public:
        void update() override;
    private:
        glm::vec3 m_gravity { 0, 9.81, 0 };

        static void get_collisions(entity::ECRigidBody &rigid_body, std::vector<physics::Collision> &collisions) ;
    };
}
