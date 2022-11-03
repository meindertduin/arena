#include "physics_system.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_physics.h"
#include "../entity/ec_collision_box.h"

#include "../global.h"
#include "../game/game_state.h"
#include "collision.h"
#include "solver.h"

namespace physics {
    void PhysicsSystem::update() {
        auto collision_component_array = global.ecs->get_component_array<entity::ECCollision>();

        for (auto entity_a : entities) {
            auto &transform = entity_a.get<entity::ECTransform>();
            auto &physics = entity_a.get<entity::ECPhysics>();
            auto &ec_collision = entity_a.get<entity::ECCollision>();

            physics.force += physics.mass * m_gravity;
            physics.velocity += physics.force / physics.mass * 1.0f/60.0f;
            transform.move(physics.velocity, - 1.0f/60.0f);

            physics.force = glm::vec3 { 0, 0, 0 };


            // Object ec_collision
            std::vector<physics::Collision> collisions;
            for (auto & e_it : *collision_component_array) {
                auto entity_b = e_it.second.entity;
                if (entity_a == entity_b) continue;

                auto &other_transform = entity_b.get<entity::ECTransform>();
                auto &other_collider = entity_b.get<entity::ECCollision>();

                auto collision_points = ec_collision.collider()->test_collision(transform, other_collider.collider().get(), other_transform);
                if (collision_points.has_collision) {
                    collisions.push_back(physics::Collision{ entity_a, entity_b, &transform, &other_transform, collision_points });
                }
            }

            physics::PositionSolver solver;
            solver.solve(collisions, 0.0f);

            // Terrain ec_collision
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