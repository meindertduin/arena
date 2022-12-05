#include "model.h"
#include "../math/helpers.h"
#include "../global.h"
#include "../assets/cache.h"

namespace graphics {
    void Model::load(std::size_t size, char *data) {
        auto model_data = reinterpret_cast<ModelData*>(data);

        auto material = global.cache->get_resource<graphics::Material>("scripts/material.lua");
        auto texture = global.cache->get_resource<graphics::Texture>("assets/fan_tree.png");
        auto shader = global.cache->get_resource<graphics::Shader>("scripts/light_shader.lua");

        material->add_texture(texture);
        material->set_shader(shader);

        // TODO remove test code
        material->shader()->program().use();
        material->shader()->program().set_uniform_loc("baseTexture", 0);
        material->shader()->program().set_uniform_loc("cubeMap", 1);

        m_aabb = math::AABB::create_min();

        for (auto mesh_data : model_data->meshes) {
            m_meshes.emplace_back(mesh_data, material);
            auto mesh_aabb = math::AABB { mesh_data->max };
            m_aabb = { math::merge_min(m_aabb.min(), mesh_aabb.min()), math::merge_max(m_aabb.max(), mesh_aabb.max()) };
        }
    }
}