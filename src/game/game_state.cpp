#include "game_state.h"
#include "../global.h"
#include "../entity/ec_player.h"
#include "../graphics/graphic_options.h"

namespace game {
    GameState::GameState() {
        graphics::DirLight dir_light;                
        dir_light.direction = { 0, -1.0f, -1.0f };  
        dir_light.ambient = {0.05f, 0.05f, 0.05f};
        dir_light.diffuse = {0.8f, 0.8f, 0.8f};   
        dir_lights.push_back(dir_light);

        graphics::PointLight pointLight;
        pointLight.position = { 2.0f, 2.0f, 0 };
        pointLight.ambient = {0.2f, 0.2f, 0.2f};
        pointLight.diffuse = {0.8f, 0.8f, 0.8f};
        pointLight.specular = {0.5f, 0.5f, 0.5f};
        pointLight.constant = 0.5f;
        pointLight.linear = 0.09f;
        pointLight.quadratic = 0.032f;

        point_lights.push_back(pointLight);

        this->camera = new entity::Camera { global.graphic_options->screen_dimensions.x, global.graphic_options->screen_dimensions.y };
    }

    GameState::~GameState() {
        delete camera;
    }

    void GameState::init() {
       // loading map
        this->map = std::make_unique<Map>();

        this->player = entity::ECPlayer::create(global.ecs->create_entity());
        this->cube = global.ecs->create_entity();
        auto mesh_renderer = entity::EcStaticMeshRenderer();
        mesh_renderer.init("assets/cube.obj");
        this->cube.add(mesh_renderer);
        this->cube.add(entity::ECTransform({ 0, -18, -10 }, {}));
    }
}
