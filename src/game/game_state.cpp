#include "game_state.h"
#include "../global.h"
#include "../entity/ec_player.h"
#include "../graphics/graphic_options.h"
#include "../entity/systems_collection.h"

#include "../graphics/renderer.h"
#include "../core/program_time.h"
#include "../entity/ec_collision.h"

namespace game {
    GameState::GameState() : m_camera{ global.graphic_options->size().width(), global.graphic_options->size().height() } {
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
    }

    void GameState::init() {
       // loading map
        this->m_map = std::make_unique<Map>();

        this->cube = global.ecs->create_entity();
        auto mesh_renderer = entity::EcStaticMeshRenderer();
        mesh_renderer.init("assets/fan_tree.obj");
        auto collision = entity::ECCollision();
        collision.init("assets/fan_tree.obj");
        this->cube.add(mesh_renderer);
        this->cube.add(collision);
        this->cube.add(entity::ECTransform({ 0, -24, -10 }, {}));

        this->m_player = entity::ECPlayer::create(global.ecs->create_entity());
    }

    void GameState::update() {
        global.systems->update();

        if (m_ui_mode)
            m_ui.on_tick(core::TotalTicks);
    }

    void GameState::render() {
        global.renderer->before_render();

        m_map->render_background();
        global.systems->render();
        m_skybox.render();

        if (m_ui_mode)
            m_ui.render();

        global.renderer->after_render();
    }
}
