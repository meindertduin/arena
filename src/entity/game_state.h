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

            graphics::PointLight pointLight;
            pointLight.position = { 2.0f, 2.0f, 0 };
            pointLight.ambient = {0.2f, 0.2f, 0.2f};
            pointLight.diffuse = {0.8f, 0.8f, 0.8f};
            pointLight.specular = {0.5f, 0.5f, 0.5f};
            pointLight.constant = 0.5f;
            pointLight.linear = 0.09f;
            pointLight.quadratic = 0.032f;

            point_lights.push_back(pointLight);
        }

        ~GameState() {
            delete camera;
        }

        std::vector<graphics::DirLight> dir_lights;
        std::vector<graphics::PointLight> point_lights;

        entity::Camera *camera;
    };
}
