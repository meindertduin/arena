#include "physics_system.h"
#include "../global.h"
#include "../game/game_state.h"
#include "collision.h"
#include "solver.h"

namespace physics {
    void PhysicsSystem::update() {
        for (auto entity_a : entities) {
            auto &rigid_body = entity_a.get<entity::ECRigidBody>();
            auto &transform = entity_a.get<entity::ECTransform>();

            rigid_body.force += rigid_body.mass * m_gravity;
            rigid_body.velocity += rigid_body.force / rigid_body.mass * 1.0f/60.0f;

            transform.move(rigid_body.velocity, - 1.0f/60.0f);

            rigid_body.force = glm::vec3 { 0, 0, 0 };

            auto colliding_objects = global.game->active_scene()->octree().get_colliding_objects(rigid_body);

            printf("colliding objects: %lu\n", colliding_objects.size());

            // Object collision
            std::vector<physics::Collision> collisions;

            for (auto value : colliding_objects) {
                auto collision_points = rigid_body.test_collision(*value);

                if (collision_points.has_collision) {
                    collisions.push_back(physics::Collision { &rigid_body, value, collision_points });
                }
            }

            physics::PositionSolver solver;
            solver.solve(collisions, 0.0f);

            // Terrain collision
            auto terrain = global.game->active_scene()->map()->terrain;
            float height;
            auto in_terrain_range = terrain->get_height(transform.pos.x, transform.pos.z, height);

            if (in_terrain_range && height > transform.pos.y - 2) {
                transform.pos.y = height + 2;
                rigid_body.velocity = glm::vec3 { 0, 0, 0 };
            }
        }
    }
}