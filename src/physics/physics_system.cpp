#include "physics_system.h"
#include "../global.h"
#include "../game/game_state.h"
#include "collision.h"
#include "solver.h"
#include "physics_object.h"

namespace physics {
    void PhysicsSystem::update() {
        auto collision_component_array = global.ecs->get_component_array<entity::ECRigidBody>();
        for (auto entity_a : entities) {
            PhysicsObject phy_object_a { entity_a };
            auto physics = phy_object_a.physics().value();

            physics->force += physics->mass * m_gravity;
            physics->velocity += physics->force / physics->mass * 1.0f/60.0f;

            phy_object_a.transform()->move(physics->velocity, - 1.0f/60.0f);

            physics->force = glm::vec3 { 0, 0, 0 };

            auto colliding_objects = global.game->octree().get_colliding_objects(phy_object_a);

            // Object collision
            std::vector<physics::Collision> collisions;

            printf("colliding objects: %lu\n", colliding_objects.size());

            for (auto value : colliding_objects) {
                auto collision_points = phy_object_a.test_collision(*value);

                if (collision_points.has_collision) {
                    collisions.push_back(physics::Collision { &phy_object_a, value, collision_points });
                }
            }

            physics::PositionSolver solver;
            solver.solve(collisions, 0.0f);

            // Terrain collision
            auto terrain = global.game->map()->terrain;
            float height;
            auto in_terrain_range = terrain->get_height(phy_object_a.transform()->pos.x, phy_object_a.transform()->pos.z, height);

            if (in_terrain_range && height > phy_object_a.transform()->pos.y - 2) {
                phy_object_a.transform()->pos.y = height + 2;
                physics->velocity = glm::vec3 { 0, 0, 0 };
            }
        }
    }
}