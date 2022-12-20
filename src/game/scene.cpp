#include "scene.h"
#include "../global.h"

#include "../graphics/graphic_options.h"
#include "../graphics/renderer.h"
#include "../entity/ec_factory.h"
#include "../entity/ec_control.h"

namespace game {
    void Scene::initialize() {
        m_ecs = std::make_unique<entity::Ecs>(this);

        pm_physics_system = m_ecs->create_system<physics::PhysicsSystem>({ entity::ECRigidBody::_id });
        pm_movement_system = m_ecs->create_system<entity::MovementSystem>({ entity::ECControl::_id, entity::ECTransform::_id });

        m_render_world = RenderWorld::create(*this, *global.renderer);

        m_player = entity::ECFactory::create_player(m_ecs->create_entity());
        entity::ECFactory::create_tree(m_ecs->create_entity());

        m_static_octree.reset();
        auto collision_objects = m_ecs->get_component_array<entity::ECCollisionObject>()->values();
        m_static_octree.fill_with_objects(collision_objects);
    }

    void Scene::update() {
        m_dynamic_octree.reset();
        auto collision_objects = m_ecs->get_component_array<entity::ECRigidBody>()->values();
        m_dynamic_octree.fill_with_objects(collision_objects);

        // TODO remove
        pm_movement_system->update();
        pm_physics_system->update();
    }

    void Scene::render() {
        global.renderer->before_render();

        m_map->render_background();
        m_render_world->update();
        m_skybox.render();

        global.renderer->after_render();
    }

    Scene::Scene() :
        m_camera{global.graphic_options->size().width(), global.graphic_options->size().height()}
    {
    }
}