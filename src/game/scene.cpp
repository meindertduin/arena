#include "scene.h"
#include "../global.h"
#include "../entity/ec_player.h"
#include "../entity/systems_collection.h"

#include "../graphics/graphic_options.h"

namespace game {
    void Scene::init() {
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

        this->m_player = entity::ECPlayer::create(global.ecs->create_entity());

        auto collision_component_array = global.ecs->get_component_array<entity::ECRigidBody>();
        for (auto &col : *collision_component_array) {
            m_physics_objects.push_back(new physics::PhysicsObject { col.second.entity });
        }
    }

    void Scene::update() {
        m_octree.reset();
        m_octree.fill_with_objects(m_physics_objects);
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