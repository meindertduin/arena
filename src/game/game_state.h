#pragma once

#include "../graphics/light.h"
#include "../entity/camera.h"
#include "../assets/cache.h"

#include "map.h"
#include "../ui/ui.h"

namespace game {
    class GameState {
    public:
        GameState();
        ~GameState();

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

        ui::UI ui;
        bool ui_mode {false};

        std::vector<graphics::DirLight> dir_lights;
        std::vector<graphics::PointLight> point_lights;

        assets::Cache cache;
        entity::Camera *camera;
        entity::Entity player;
        entity::Entity cube;

        std::unique_ptr<Map> map;

        void init();
        void update();
        void render();
    };
}
