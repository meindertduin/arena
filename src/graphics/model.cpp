#include "model.h"
#include "../math/helpers.h"
#include "../global.h"
#include "../assets/cache.h"
#include "../assets/loaders.h"

namespace graphics {
    void Model::load() {
        auto model_mesh_data = assets::load_obj(path());
        ModelData model_data;
        model_data.meshes.push_back(model_mesh_data.get());

        auto cache = global.application->engine()->cache();
        auto material = cache->get_resource<graphics::Material>("scripts/material.lua");
        auto texture = cache->get_resource<graphics::Texture>("assets/fan_tree.png");
        auto shader = cache->get_resource<graphics::Shader>("scripts/light_shader.lua");

        material->add_texture(texture);
        material->set_shader(shader);

        m_aabb = math::AABB::create_min();

        for (auto mesh_data : model_data.meshes) {
            m_meshes.emplace_back(mesh_data, material);
            auto mesh_aabb = math::AABB { mesh_data->max };
            m_aabb = { math::merge_min(m_aabb.min(), mesh_aabb.min()), math::merge_max(m_aabb.max(), mesh_aabb.max()) };
        }
    }

    void Model::set_state(ModelState state) {
        m_state = state;
    }
}