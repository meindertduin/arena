#include "mesh.h"

#include <glad/glad.h>

namespace graphics {
    Mesh::Mesh(MeshData *mesh_data, const math::AABB &box)
            : m_bounding_box{box} {
        m_mesh_data = std::unique_ptr<MeshData>(mesh_data);

        this->buffer_array.set_data(0, sizeof(Vertex) * mesh_data->vertices.size(), mesh_data->vertices.data());
        this->vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        this->vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        this->vertex_buffer.add_vertex_attribute({2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true});

        this->size = mesh_data->vertices.size();
    }

    void Mesh::render() const {
        this->buffer_array.bind();

        this->vertex_buffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, this->size);
    }

    void Mesh::add_collision_data(MeshData *collision_data) {
        m_collisions_data.push_back(std::shared_ptr<MeshData>(collision_data));
    }
}

