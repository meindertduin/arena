#include "terrain_collision_system.h"

#include "ec_collision_box.h"
#include "../global.h"

namespace entity {
    void TerrainCollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision_box = entity.get<ECCollisionBox>();
            auto &transform = entity.get<ECTransform>();

            if (collision_box.min_y + transform.pos.y < -1) {
                transform.pos.y = 0;
            }
        }
    }
}
