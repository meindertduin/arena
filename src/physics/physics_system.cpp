#include "physics_system.h"
#include "../entity/ec_transform.h"

namespace physics {
    void PhysicsSystem::update() {
        for(auto entity : entities) {
            auto &transform = entity.get<entity::ECTransform>();

            transform.move({ 0, 1, 0}, -0.50f);
        }
    }
}
