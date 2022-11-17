#pragma once

#include <vector>
#include "../graphics/light.h"
#include "../entity/camera.h"
#include "../entity/entity.h"
#include "../graphics/skybox.h"
#include "map.h"
#include "../physics/octree.h"

namespace game {
    class Scene {
    public:
        Scene();

        constexpr ALWAYS_INLINE graphics::Skybox& skybox() { return m_skybox; }
        constexpr ALWAYS_INLINE std::unique_ptr<Map>& map() { return m_map; }

        constexpr ALWAYS_INLINE std::vector<graphics::DirLight>& dir_lights() { return m_dir_lights; }
        constexpr ALWAYS_INLINE std::vector<graphics::PointLight>& point_lights() { return m_point_lights; }

        constexpr ALWAYS_INLINE entity::Camera& camera() { return m_camera; }

        constexpr ALWAYS_INLINE entity::Entity player() { return m_player; }
        constexpr ALWAYS_INLINE physics::Octree<entity::ECCollisionObject>& static_octree() { return m_static_octree; }

        void init();
        void update();
        void render();

    private:
        graphics::Skybox m_skybox;
        std::unique_ptr<Map> m_map;

        std::unordered_map<int, entity::Entity> m_entities;

        std::vector<graphics::DirLight> m_dir_lights;
        std::vector<graphics::PointLight> m_point_lights;

        entity::Camera m_camera;

        entity::Entity m_player{};
        physics::Octree<entity::ECCollisionObject> m_static_octree {500.0f, 8 };
    };
}