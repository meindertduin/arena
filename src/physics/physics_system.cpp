#include "physics_system.h"
#include "../global.h"
#include "../game/scene.h"
#include "collision.h"
#include "solver.h"

namespace physics {
    void PhysicsSystem::update() {
        for (auto entity_a : entities) {
            auto &rigid_body = entity_a.get<entity::ECRigidBody>();
            auto &transform = entity_a.get<entity::ECTransform>();

            apply_gravity(rigid_body, transform);

            std::vector<physics::Collision> collisions;
            get_collisions(rigid_body, collisions);

            physics::PositionSolver solver;
            solver.solve(collisions, 0.0f);

            test_terrain_collision(rigid_body, transform);
        }
    }

    void PhysicsSystem::apply_gravity(entity::ECRigidBody &rigid_body, entity::ECTransform &transform) const {
        rigid_body.force += rigid_body.mass * m_gravity;
        rigid_body.velocity += rigid_body.force / rigid_body.mass * 1.0f/60.0f;

        transform.move(rigid_body.velocity, - 1.0f/60.0f);

        rigid_body.force = glm::vec3 { 0, 0, 0 };
    }

    void PhysicsSystem::get_collisions(entity::ECRigidBody &rigid_body, std::vector<physics::Collision> &collisions) {
        auto active_scene = global.application->engine()->active_scene();
        auto colliding_static_objects = active_scene->static_octree().get_colliding_objects(rigid_body);
        auto colliding_dynamic_objects = active_scene->dynamic_octree().get_colliding_objects(rigid_body);

        for (auto value : colliding_static_objects) {
            auto collision_points = rigid_body.test_collision(value);

            if (collision_points.has_collision) {
                collisions.push_back(Collision {&rigid_body, value, collision_points });
            }
        }

        for (auto value : colliding_dynamic_objects) {
            auto collision_points = rigid_body.test_collision(value);

            if (collision_points.has_collision) {
                collisions.push_back(Collision {&rigid_body, value, collision_points });
            }
        }
    }

    void PhysicsSystem::test_terrain_collision(entity::ECRigidBody &rigid_body, entity::ECTransform &transform) {
        auto active_scene = global.application->engine()->active_scene();

        auto terrain = active_scene->map()->terrain;
        float height;
        auto in_terrain_range = terrain->get_height(transform.pos.x, transform.pos.z, height);

        if (in_terrain_range && height > transform.pos.y - 2) {
            transform.pos.y = height + 2;
            rigid_body.velocity = glm::vec3 { 0, 0, 0 };
        }
    }
}
