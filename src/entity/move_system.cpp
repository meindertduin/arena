#include "move_system.h"

#include "../global.h"

namespace entity {
    void MoveSystem::update() {
        for (auto &entity : entities) {
            auto &transform = global.ecs.get_component<Transform>(entity);
            transform.pos.x -= 0.1f;
        }
    }
}
