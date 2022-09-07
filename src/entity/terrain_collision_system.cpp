#include "terrain_collision_system.h"

#include "ec_collision_box.h"
#include "../global.h"

namespace entity {
    void TerrainCollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision_box = entity.get<ECCollisionBox>();
            auto &transform = entity.get<ECTransform>();

            float height;
            auto did_intersect = global.game->map->terrain->fast_height(transform.pos.x, transform.pos.z, height);

            if (did_intersect) {
                printf("%f\n", height);
            }
            if (did_intersect && height > transform.pos.y - 1) {
                transform.pos.y = height + 1;
            }

        }
    }
}
