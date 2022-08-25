#pragma once

#include "../graphics/light.h"

#include "camera.h"

namespace entity {
    struct GameState {
    public:
        GameState() {
            graphics::DirLight dir_light;                
            dir_light.direction = { 0, -1.0f, -1.0f };  
            dir_light.ambient = {0.05f, 0.05f, 0.05f};
            dir_light.diffuse = {0.8f, 0.8f, 0.8f};   
            dir_lights.push_back(dir_light);
        }

        ~GameState() {
            delete camera;
        }

        std::vector<graphics::DirLight> dir_lights;
        std::vector<graphics::PointLight> point_lights;

        entity::Camera *camera;
    };
}
