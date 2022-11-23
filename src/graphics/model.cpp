#include "model.h"

namespace graphics {
    void Model::render() {
        for (auto &mesh : m_meshes) {
            mesh->render();
        }
    }

    void Model::load(std::size_t size, char *data) {
        auto model_data = reinterpret_cast<ModelData*>(data);
        for (auto mesh_data : model_data->meshes) {
            m_meshes.push_back(std::make_unique<Mesh>(mesh_data));
        }
    }
}