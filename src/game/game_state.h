#pragma once

#include "../graphics/light.h"
#include "../entity/camera.h"
#include "../assets/cache.h"

#include "map.h"
#include "../ui/ui.h"
#include "../graphics/skybox.h"
#include "../physics/octree.h"
#include "scene.h"

#include <thread>

namespace game {
    enum class Mode {
        Editing,
        Playing,
    };

    class GameState {
    public:
        GameState();

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;

        constexpr ALWAYS_INLINE bool ui_mode() const { return m_ui_mode; }
        ALWAYS_INLINE void set_ui_mode(bool new_ui_mode) { m_ui_mode = new_ui_mode; }

        constexpr ALWAYS_INLINE Mode game_mode() const { return m_game_mode; }
        ALWAYS_INLINE void set_game_mode(Mode new_game_mode) { m_game_mode = new_game_mode; }

        constexpr ALWAYS_INLINE ui::UI& ui() { return m_ui; }

        constexpr ALWAYS_INLINE assets::Cache& cache() { return m_cache; }
        constexpr ALWAYS_INLINE std::unique_ptr<Scene>& active_scene() { return m_active_scene; }
        constexpr ALWAYS_INLINE lua_State* lua_state() { return m_lua_state; }

        void init();
        void update();
        void render();
    private:
        bool m_ui_mode { false };
        Mode m_game_mode { Mode::Playing };
        ui::UI m_ui;

        assets::Cache m_cache;
        lua_State *m_lua_state;
        std::unique_ptr<Scene> m_active_scene { nullptr };
    };
}