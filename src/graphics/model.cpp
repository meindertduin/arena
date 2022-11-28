#include "model.h"
#include "../math/helpers.h"
#include "../global.h"
#include "../game/game_state.h"

namespace graphics {
    void Model::load(std::size_t size, char *data) {
        auto model_data = reinterpret_cast<ModelData*>(data);

        auto material = std::make_shared<graphics::Material>(glm::vec3{ 0.2f, 0.2f, 0.2f }, glm::vec3{ 0.6f, 0.6f, 0.6f }, glm::vec3{ 0.2f, 0.2f, 0 }, 0.2f);
        auto texture = global.game->cache().get_resource<graphics::Texture>("assets/fan_tree.png");

        material->add_texture(texture);
        material->set_shader(std::make_shared<graphics::ShaderProgram>("shaders/light_shader"));

        // TODO remove test code
        material->shader()->use();
        material->shader()->set_uniform_loc("baseTexture", 0);
        material->shader()->set_uniform_loc("cubeMap", 1);

        m_aabb = math::AABB::create_min();

        for (auto mesh_data : model_data->meshes) {
            m_meshes.emplace_back(mesh_data, material);
            auto mesh_aabb = math::AABB { mesh_data->max };
            m_aabb = { math::merge_min(m_aabb.min(), mesh_aabb.min()), math::merge_max(m_aabb.max(), mesh_aabb.max()) };
        }
    }
}