#include "systems_collection.h"

#include "../global.h"
#include "ec_static_mesh.h"
#include "ec_physics.h"
#include "ec_control.h"
#include "ec_transform.h"

namespace entity {
    void SystemsCollection::init() {
        pm_static_render_system = global.ecs->create_system<entity::StaticRenderSystem>({ EcStaticMeshRenderer::_id });
        pm_physics_system = global.ecs->create_system<physics::PhysicsSystem>({ entity::ECPhysics::_id });
        pm_movement_system = global.ecs->create_system<entity::MovementSystem>({ entity::ECControl::_id, entity::ECTransform::_id });
    }

    void SystemsCollection::update(float ft) {
        pm_movement_system->update(ft);
        pm_physics_system->update(ft);
    }

    void SystemsCollection::render() {
        pm_static_render_system->update(1.0f);
    }
}