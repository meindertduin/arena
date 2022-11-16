#include "game_state.h"
#include "../global.h"

#include "../graphics/renderer.h"
#include "../core/program_time.h"

#include "../entity/systems_collection.h"

namespace game {
    void GameState::init() {
       // loading map
        this->cube = global.ecs->create_entity();
        auto collision = entity::ECRigidBody(false);

        auto tree_mesh = m_cache.get_resource<graphics::Mesh>("assets/fan_tree.obj");

        auto mesh_renderer = entity::EcStaticMeshRenderer(tree_mesh);
        collision.set_collider(std::make_shared<physics::MeshCollider>(tree_mesh));

        this->cube.add(mesh_renderer);
        this->cube.add(collision);
        this->cube.add(entity::ECTransform({ 0, -24, -10 }, {}));

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
