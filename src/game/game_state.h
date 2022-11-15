#pragma once

#include "../graphics/light.h"
#include "../entity/camera.h"
#include "../assets/cache.h"

#include "map.h"
#include "../ui/ui.h"
#include "../graphics/skybox.h"
#include "../physics/octree.h"

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

        // TODO remove and implement entity storage
        entity::Entity cube{};

        constexpr ALWAYS_INLINE bool ui_mode() const { return m_ui_mode; }
        ALWAYS_INLINE void set_ui_mode(bool new_ui_mode) { m_ui_mode = new_ui_mode; }

        constexpr ALWAYS_INLINE Mode game_mode() const { return m_game_mode; }
        ALWAYS_INLINE void set_game_mode(Mode new_game_mode) { m_game_mode = new_game_mode; }

        constexpr ALWAYS_INLINE ui::UI& ui() { return m_ui; }

        constexpr ALWAYS_INLINE assets::Cache& cache() { return m_cache; }
        constexpr ALWAYS_INLINE entity::Entity player() const { return m_player; }
        constexpr ALWAYS_INLINE graphics::Skybox& skybox() { return m_skybox; }
        constexpr ALWAYS_INLINE std::unique_ptr<Map>& map() { return m_map; }

        constexpr ALWAYS_INLINE std::vector<graphics::DirLight>& dir_lights() { return m_dir_lights; }
        constexpr ALWAYS_INLINE std::vector<graphics::PointLight>& point_lights() { return m_point_lights; }
        constexpr ALWAYS_INLINE entity::Camera& camera() { return m_camera; }

        constexpr ALWAYS_INLINE physics::Octree& octree() { return m_octree; }

        void init();
        void update();
        void render();
    private:
        bool m_ui_mode { false };
        Mode m_game_mode { Mode::Playing };
        ui::UI m_ui;

        assets::Cache m_cache;
        entity::Entity m_player{};
        graphics::Skybox m_skybox;
        std::unique_ptr<Map> m_map;

        std::vector<graphics::DirLight> m_dir_lights;
        std::vector<graphics::PointLight> m_point_lights;

        physics::Octree m_octree { 500.0f, 8 };

        entity::Camera m_camera;
    };
}