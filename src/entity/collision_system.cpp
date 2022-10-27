#include "collision_system.h"
#include "ec_collision.h"

namespace entity {
    void CollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision = entity.get<ECCollision>();
            auto &transform = entity.get<ECTransform>();

            auto &box = collision.mesh()->bounding_box();
            box.set_center(transform.pos);

            for (auto &other_entity : entities) {
                if (other_entity.id != entity.id) {
                    auto &other_transform = other_entity.get<ECTransform>();
                    auto &other_box = other_entity.get<ECCollision>().mesh()->bounding_box();

                    other_box.set_center(other_transform.pos);

                    if (box.inside(other_box)) {
                        printf("entities collide\n");
                    }
                }
            }
        }
    }
}
