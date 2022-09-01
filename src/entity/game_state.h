#pragma once

#include "../graphics/light.h"
#include "camera.h"
#include "../assets/cache.h"

namespace entity {
    struct GameState {
        GameState();
        ~GameState();

        GameState(const GameState&) = delete;
        GameState(GameState&&) = delete;
        GameState& operator=(const GameState&) = delete;
        GameState& operator=(GameState&&) = delete;

        std::vector<graphics::DirLight> dir_lights;
        std::vector<graphics::PointLight> point_lights;

        void init();

        assets::Cache cache;
        Camera *camera;
        Entity player;
    };
}
