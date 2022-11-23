#include "model.h"

namespace graphics {
    void Model::load(std::size_t size, char *data) {
        auto model_data = reinterpret_cast<ModelData*>(data);

        for (auto mesh_data : model_data->meshes) {
            m_meshes.push_back(std::make_unique<Mesh>(mesh_data));
        }

        m_aabb = math::AABB{ model_data->meshes[0]->max };
    }
}