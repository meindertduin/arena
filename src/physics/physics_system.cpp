#include "physics_system.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_physics.h"
#include "../entity/ec_collision_box.h"

#include "../global.h"
#include "../game/game_state.h"
#include "collision.h"
#include "../entity/ec_collision.h"

namespace physics {
    void PhysicsSystem::update() {
        std::vector<Collision> collisions;
        auto collision_component_array = global.ecs->get_component_array<entity::ECCollision>();

        for (auto entity_a : entities) {
            auto &transform = entity_a.get<entity::ECTransform>();
            auto &physics = entity_a.get<entity::ECPhysics>();
            auto &collision = entity_a.get<entity::ECCollision>();

            physics.force += physics.mass * m_gravity;
            physics.velocity += physics.force / physics.mass * 1.0f/60.0f;
            transform.move(physics.velocity, - 1.0f/60.0f);

            physics.force = glm::vec3 { 0, 0, 0 };

            auto &box = collision.mesh()->bounding_box();
            box.set_center(transform.pos);

            // Object collision
            for (auto & e_it : *collision_component_array) {
                auto entity_b = e_it.second.entity;
                if (entity_a == entity_b) continue;

                auto &other_transform = entity_b.get<entity::ECTransform>();
                auto &other_collider = entity_b.get<entity::ECCollision>();
                auto &other_box = other_collider.mesh()->bounding_box();

                other_box.set_center(other_transform.pos);

                if (box.inside(other_box)) {
                    if (physics::gjk(collision.collider().get(), other_collider.collider().get(), transform, other_transform)) {
                        printf("really collides\n");
                    }
                }
            }

            // Terrain collision
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