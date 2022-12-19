#include "scene.h"
#include "../global.h"
#include "../entity/systems_collection.h"

#include "../graphics/graphic_options.h"
#include "../entity/ec_factory.h"

namespace game {
    void Scene::initialize() {
        graphics::DirLight dir_light;
        dir_light.direction = { 0, -1.0f, -1.0f };
        dir_light.ambient = {0.05f, 0.05f, 0.05f};
        dir_light.diffuse = {0.8f, 0.8f, 0.8f};
        m_dir_lights.push_back(dir_light);

        graphics::PointLight pointLight;
        pointLight.position = { 2.0f, 2.0f, 0 };
        pointLight.ambient = {0.2f, 0.2f, 0.2f};
        pointLight.diffuse = {0.8f, 0.8f, 0.8f};
        pointLight.specular = {0.5f, 0.5f, 0.5f};
        pointLight.constant = 0.5f;
        pointLight.linear = 0.09f;
        pointLight.quadratic = 0.032f;

        m_point_lights.push_back(pointLight);

        this->m_map = std::make_unique<Map>();

        m_player = entity::ECFactory::create_player();
        entity::ECFactory::create_tree();

        m_static_octree.reset();
        auto collision_objects = global.ecs->get_component_array<entity::ECCollisionObject>()->values();
        m_static_octree.fill_with_objects(collision_objects);
    }

    void Scene::update() {
        m_dynamic_octree.reset();
        auto collision_objects = global.ecs->get_component_array<entity::ECRigidBody>()->values();
        m_dynamic_octree.fill_with_objects(collision_objects);
    }

    void Scene::render() {
        m_map->render_background();
        global.systems->render();
        m_skybox.render();
    }

    Scene::Scene() :
        m_camera{global.graphic_options->size().width(), global.graphic_options->size().height()}
    {
    }
}