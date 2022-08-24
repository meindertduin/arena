#pragma once

#include "../graphics/light.h"

#include "camera.h"

namespace entity {
    struct GameState {
    public:
        ~GameState() {
            delete camera;
        }

        std::vector<graphics::DirLight> dir_lights;
        std::vector<graphics::PointLight> point_lights;

        entity::Camera *camera;
    };
}
