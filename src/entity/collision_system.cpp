#include "collision_system.h"
#include "ec_collision.h"

namespace entity {
    void CollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision = entity.get<ECCollision>();
            auto &transform = entity.get<ECTransform>();

            auto &box = collision.mesh()->bounding_box();
            // iterate over all other close collision boxes
        }
    }
}
