#pragma once

#include "../graphics/light.h"
#include "../entity/camera.h"

#include "map.h"
#include "../graphics/skybox.h"
#include "../physics/octree.h"
#include "scene.h"

#include <thread>

namespace game {
    class GameState {
    public:
        GameState() = default;

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

        constexpr ALWAYS_INLINE std::unique_ptr<Scene>& active_scene() { return m_active_scene; }

        void init();
        void update();
        void render();

    private:
        std::unique_ptr<Scene> m_active_scene { nullptr };
    };
}