#include "game_state.h"
#include "../global.h"

#include "../graphics/renderer.h"
#include "../entity/systems_collection.h"

namespace game {
    void GameState::init() {
        m_active_scene = std::make_unique<Scene>();
        m_active_scene->initialize();
    }

    void GameState::update() {
        m_active_scene->update();

        global.systems->update();
    }

    void GameState::render() {
        global.renderer->before_render();

        m_active_scene->render();

        global.renderer->after_render();
    }
}
