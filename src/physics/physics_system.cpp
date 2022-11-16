#include "physics_system.h"
#include "../global.h"
#include "../game/game_state.h"
#include "collision.h"
#include "solver.h"

namespace physics {
    void PhysicsSystem::update() {
        auto collision_component_array = global.ecs->get_component_array<entity::ECCollisionObject>();
        for (auto entity_a : entities) {
            auto &rigid_body = entity_a.get<entity::ECRigidBody>();

            rigid_body.force += rigid_body.mass * m_gravity;
            rigid_body.velocity += rigid_body.force / rigid_body.mass * 1.0f/60.0f;

            rigid_body.transform()->move(rigid_body.velocity, - 1.0f/60.0f);

            rigid_body.force = glm::vec3 { 0, 0, 0 };

            auto colliding_objects = global.game->active_scene()->octree().get_colliding_objects(entity_a);

            printf("colliding objects: %lu\n", colliding_objects.size());

            // Object collision
            std::vector<physics::Collision> collisions;

            for (auto value : colliding_objects) {
                auto &other_collision_object = value.get<entity::ECCollisionObject>();
                auto collision_points = rigid_body.test_collision(other_collision_object);

                if (collision_points.has_collision) {
                    collisions.push_back(physics::Collision { &rigid_body, &other_collision_object, collision_points });
                }
            }

            physics::PositionSolver solver;
            solver.solve(collisions, 0.0f);

            // Terrain collision
            auto terrain = global.game->active_scene()->map()->terrain;
            float height;
            auto in_terrain_range = terrain->get_height(rigid_body.transform()->pos.x, rigid_body.transform()->pos.z, height);

            if (in_terrain_range && height > rigid_body.transform()->pos.y - 2) {
                rigid_body.transform()->pos.y = height + 2;
                rigid_body.velocity = glm::vec3 { 0, 0, 0 };
            }
        }
    }
}