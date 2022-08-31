#include "game_state.h"
#include "../global.h"
#include "ec_player.h"

namespace entity {
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
        ECPlayer ec_player;
        this->player = ec_player.create(global.ecs->create_entity());
    }
}
