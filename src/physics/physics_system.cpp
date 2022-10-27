#include "physics_system.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_physics.h"

namespace physics {
    void PhysicsSystem::update() {
        for(auto entity : entities) {
            auto &transform = entity.get<entity::ECTransform>();
            auto &physics = entity.get<entity::ECPhysics>();

            physics.force += physics.mass * m_gravity;

            physics.velocity += physics.force / physics.mass * 1.0f/60.0f;
            transform.move(physics.velocity, - 1.0f/60.0f);

            physics.force = glm::vec3 { 0, 0, 0 };
        }
    }
}