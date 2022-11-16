#include "game_state.h"
#include "../global.h"

#include "../graphics/renderer.h"
#include "../core/program_time.h"

#include "../entity/systems_collection.h"

namespace game {
    void GameState::init() {
        m_active_scene->init();
    }

    void GameState::update() {
        m_active_scene->update();

        global.systems->update();

        // TODO: use state pattern for handling update
        if (m_ui_mode)
            m_ui.on_tick(core::TotalTicks);
    }

    void GameState::render() {
        global.renderer->before_render();

        m_active_scene->render();

        if (m_ui_mode)
            m_ui.render();

        global.renderer->after_render();
    }

    GameState::GameState() {
        m_active_scene = std::make_unique<Scene>();
    }
}
