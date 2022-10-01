#include "systems_collection.h"

#include "../global.h"
#include "ec_static_mesh.h"
#include "ec_physics.h"
#include "ec_collision_box.h"
#include "ec_control.h"
#include "ec_transform.h"

namespace entity {
    void SystemsCollection::init() {
        static_render_system = global.ecs->create_system<entity::StaticRenderSystem>({ EcStaticMeshRenderer::_id });
        physics_system = global.ecs->create_system<physics::PhysicsSystem>({ entity::ECPhysics::_id });
        terrain_collision_system = global.ecs->create_system<entity::TerrainCollisionSystem>({ entity::ECCollisionBox::_id });
        movement_system = global.ecs->create_system<entity::MovementSystem>({ entity::ECControl::_id, entity::ECTransform::_id });
    }

    void SystemsCollection::update() {
        movement_system->update();
        physics_system->update();
        terrain_collision_system->update();
    }

    void SystemsCollection::render() {
        static_render_system->update();
    }
}