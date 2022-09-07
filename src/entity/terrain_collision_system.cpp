#include "terrain_collision_system.h"

#include "ec_collision_box.h"
#include "../global.h"

namespace entity {
    void TerrainCollisionSystem::update() {
        for (auto &entity : entities) {
            auto &collision_box = entity.get<ECCollisionBox>();
            auto &transform = entity.get<ECTransform>();

            glm::vec3 intersect;
            auto pos = transform.pos;
            pos.y -= 1;
            auto did_intersect = global.game->map->terrain->get_intersect(transform.pos, intersect);

            if (did_intersect && intersect.y > transform.pos.y - 1) {
                intersect.y += 1;
                transform.pos = intersect;
            }

        }
    }
}
