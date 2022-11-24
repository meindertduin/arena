#include "systems_collection.h"

#include "../global.h"
#include "ec_static_model.h"
#include "ec_control.h"
#include "ec_rigid_body.h"
#include "ec_transform.h"

namespace entity {
    void SystemsCollection::init() {
        pm_static_render_system = global.ecs->create_system<entity::StaticRenderSystem>({ECStaticModel::_id });
        pm_physics_system = global.ecs->create_system<physics::PhysicsSystem>({ entity::ECRigidBody::_id });
        pm_movement_system = global.ecs->create_system<entity::MovementSystem>({ entity::ECControl::_id, entity::ECTransform::_id });
    }

    void SystemsCollection::update() {
        pm_movement_system->update();
        pm_physics_system->update();
    }

    void SystemsCollection::render() {
        pm_static_render_system->update();
    }
}