#include "terrain_collision_system.h"

#include "ec_collision_box.h"
#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    void TerrainCollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision_box = entity.get<ECCollisionBox>();
            auto &transform = entity.get<ECTransform>();

            float height;
            auto in_terrain_range = global.game->map->terrain.get()->fast_height(transform.pos.x, transform.pos.z, height);

            if (in_terrain_range && height > transform.pos.y - 1) {
                transform.pos.y = height + 1;
            }
        }
    }
}
