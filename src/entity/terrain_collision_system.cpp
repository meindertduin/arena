#include "terrain_collision_system.h"

#include "ec_collision_box.h"
#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    void TerrainCollisionSystem::update() {
        auto terrain = global.game->map()->terrain;
        for (auto &entity : entities) {
            auto &collision_box = entity.get<ECCollisionBox>();
            auto &transform = entity.get<ECTransform>();

            float height;
            auto in_terrain_range = terrain->get_height(transform.pos.x, transform.pos.z, height);

            if (in_terrain_range && height > transform.pos.y - 2) {
                transform.pos.y = height + 2;
            }
        }
    }
}
