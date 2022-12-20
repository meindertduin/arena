#pragma once

#include <vector>
#include "../graphics/light.h"
#include "../entity/camera.h"
#include "../entity/entity.h"
#include "../graphics/skybox.h"
#include "map.h"
#include "../physics/octree.h"
#include "render_world.h"

// TODO remove these imports when not needed
#include "../physics/physics_system.h"
#include "../entity/movement_system.h"

namespace game {
    class Scene {
    public:
        Scene();

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

        constexpr ALWAYS_INLINE entity::Entity player() { return m_player; }
        constexpr ALWAYS_INLINE physics::Octree<entity::ECCollisionObject>& static_octree() { return m_static_octree; }
        constexpr ALWAYS_INLINE physics::Octree<entity::ECRigidBody>& dynamic_octree() { return m_dynamic_octree; }

        void initialize();
        void update();
        void render();

        constexpr ALWAYS_INLINE std::unique_ptr<entity::Ecs>& ecs() { return m_ecs; }
        constexpr ALWAYS_INLINE std::unique_ptr<RenderWorld>& render_world() { return m_render_world; }
    private:
        std::unique_ptr<entity::Ecs> m_ecs;

        std::unique_ptr<RenderWorld> m_render_world;
        graphics::Skybox m_skybox;
        std::unique_ptr<Map> m_map;

        std::unordered_map<int, entity::Entity> m_entities;

        std::vector<graphics::DirLight> m_dir_lights;
        std::vector<graphics::PointLight> m_point_lights;

        entity::Camera m_camera;

        entity::Entity m_player{};
        physics::Octree<entity::ECCollisionObject> m_static_octree {500.0f, 8 };
        physics::Octree<entity::ECRigidBody> m_dynamic_octree {500.0f, 8 };

        // TODO move this to test worlds
        std::shared_ptr<physics::PhysicsSystem> pm_physics_system { nullptr };
        std::shared_ptr<entity::MovementSystem> pm_movement_system { nullptr };
    };
}