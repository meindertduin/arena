#include "move_system.h"

#include "../global.h"

namespace entity {
    void MoveSystem::update() {
        for (auto &entity : entities) {
            auto &transform = global.ecs.get_component<Transform>(entity);

            transform.rotate(1, { 0, 1, 0 });
        }
    }
}
