#pragma once

#include <memory>
#include <lua.hpp>
#include "../platform/platform.h"

namespace game {
    class GameState;
}
namespace assets {
    class Cache;
}


namespace core {
    class Engine {
    public:
        enum class State {
            Paused,
            Running,
            Editing,
        };

        Engine();
        ~Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void initialize();
        void update(int lag);

        [[nodiscard]] constexpr ALWAYS_INLINE State state() const { return m_state; }
        [[nodiscard]] constexpr ALWAYS_INLINE assets::Cache* cache() const { return m_cache; }
        [[nodiscard]] constexpr ALWAYS_INLINE game::GameState* game() const { return m_game; }
        [[nodiscard]] constexpr ALWAYS_INLINE lua_State* lua_state() const { return m_lua_state; }

        void set_state(State state);
    private:
        bool m_initialized { false };
        State m_state;

        assets::Cache *m_cache { nullptr };
        game::GameState *m_game { nullptr };

        lua_State *m_lua_state;
    };
}