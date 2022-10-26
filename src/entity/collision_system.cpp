#include "collision_system.h"
#include "ec_collision.h"

namespace entity {
    void CollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision = entity.get<ECCollision>();
            auto &transform = entity.get<ECTransform>();

            auto &box = collision.mesh()->bounding_box();
            box.set_rotation(transform.rotation());
            box.set_center(math::Point3D<float>{ transform.pos.x, transform.pos.y, transform.pos.z });

            for (auto &other_entity : entities) {
                if (other_entity.id != entity.id) {
                    auto &other_transform = other_entity.get<ECTransform>();
                    auto &other_box = other_entity.get<ECCollision>().mesh()->bounding_box();

                    other_box.set_rotation(other_transform.rotation());
                    other_box.set_center(math::Point3D<float>{ other_transform.pos.x, other_transform.pos.y, other_transform.pos.z });

                    if (box.inside(other_box)) {
                        printf("entities collide\n");
                    }
                }
            }
            // iterate over all other close collision boxes
        }
    }
}
