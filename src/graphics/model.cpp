#include "model.h"
#include "../math/helpers.h"

namespace graphics {
    void Model::load(std::size_t size, char *data) {
        auto model_data = reinterpret_cast<ModelData*>(data);

        m_aabb = math::AABB::create_min();
        for (auto mesh_data : model_data->meshes) {
            m_meshes.emplace_back(mesh_data);
            auto mesh_aabb = math::AABB { mesh_data->max };
            m_aabb = { math::merge_min(m_aabb.min(), mesh_aabb.min()), math::merge_max(m_aabb.max(), mesh_aabb.max()) };
        }
    }
}