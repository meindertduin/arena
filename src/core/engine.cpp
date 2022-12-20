#include "engine.h"
#include "../game/scene.h"
#include "program_time.h"
#include "../graphics/render_target.h"
#include "../global.h"
#include "../graphics/renderer.h"

namespace core {
    Engine::Engine()
            :   m_state(State::Running)
    {
    }

    Engine::~Engine() {
        delete m_active_scene;
        delete m_cache;
    }

    void Engine::set_state(Engine::State state) {
        m_state = state;
    }

    void Engine::initialize() {
        m_cache = new assets::Cache();
        m_active_scene = new game::Scene();

        auto render_target = std::make_shared<graphics::RenderTarget>();
        global.renderer = new graphics::Renderer(render_target);

        m_lua_state = luaL_newstate();
        luaL_openlibs(m_lua_state);

        m_active_scene->initialize();
    }

    void Engine::update(int lag) {
        m_active_scene->update();
        while (lag >= core::TickTimeMs) {
            core::TotalTicks++;
            lag -= core::TickTimeMs;
        }

        m_active_scene->render();
    }
}