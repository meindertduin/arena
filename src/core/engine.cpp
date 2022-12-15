#include "engine.h"
#include "../game/game_state.h"
#include "program_time.h"

namespace core {
    Engine::Engine()
            :   m_state(State::Running)
    {
    }

    Engine::~Engine() {
        delete m_game;
        delete m_cache;
    }

    void Engine::set_state(Engine::State state) {
        m_state = state;
    }

    void Engine::initialize() {
        m_cache = new assets::Cache();
        m_game = new game::GameState();

        m_lua_state = luaL_newstate();
        luaL_openlibs(m_lua_state);

        m_game->init();
    }

    void Engine::update(int lag) {
        while (lag >= core::TickTimeMs) {
            m_game->update();

            core::TotalTicks++;
            lag -= core::TickTimeMs;
        }

        m_game->render();
    }
}