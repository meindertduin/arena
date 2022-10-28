#include "systems_collection.h"

#include "../global.h"
#include "ec_static_mesh.h"
#include "ec_physics.h"
#include "ec_control.h"
#include "ec_transform.h"
#include "ec_collision.h"

namespace entity {
    void SystemsCollection::init() {
        pm_static_render_system = global.ecs->create_system<entity::StaticRenderSystem>({ EcStaticMeshRenderer::_id });
        pm_physics_system = global.ecs->create_system<physics::PhysicsSystem>({ entity::ECPhysics::_id });
        pm_movement_system = global.ecs->create_system<entity::MovementSystem>({ entity::ECControl::_id, entity::ECTransform::_id });
        pm_collision_system = global.ecs->create_system<entity::CollisionSystem>({ entity::ECCollision::_id });
    }

    void SystemsCollection::update() {
        pm_movement_system->update();
        pm_physics_system->update();
        pm_collision_system->update();
    }

    void SystemsCollection::render() {
        pm_static_render_system->update();
    }
}