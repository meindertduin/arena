#include "physics_system.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_physics.h"
#include "../entity/ec_collision_box.h"

#include "../global.h"
#include "../game/game_state.h"

namespace physics {
    void PhysicsSystem::update() {
        for(auto entity : entities) {
            auto &transform = entity.get<entity::ECTransform>();
            auto &physics = entity.get<entity::ECPhysics>();
            auto &collision_box = entity.get<entity::ECCollisionBox>();

            physics.force += physics.mass * m_gravity;

            physics.velocity += physics.force / physics.mass * 1.0f/60.0f;
            transform.move(physics.velocity, - 1.0f/60.0f);

            physics.force = glm::vec3 { 0, 0, 0 };

            auto terrain = global.game->map()->terrain;
            float height;
            auto in_terrain_range = terrain->get_height(transform.pos.x, transform.pos.z, height);

            if (in_terrain_range && height > transform.pos.y - 2) {
                transform.pos.y = height + 2;
                physics.velocity = glm::vec3 { 0, 0, 0 };
            }
        }
    }
}