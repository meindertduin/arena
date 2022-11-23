#include "mesh.h"

#include <glad/glad.h>

namespace graphics {
    void Mesh::render() const {
        this->buffer_array.bind();

        this->vertex_buffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, m_gl_size);
    }

    void Mesh::load(std::size_t size, char *data) {
        auto mesh_data = reinterpret_cast<MeshData*>(data);

        buffer_array.set_data(0, sizeof(Vertex) * mesh_data->vertices.size(), mesh_data->vertices.data());
        vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        vertex_buffer.add_vertex_attribute({2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true});

        m_gl_size = static_cast<int>(mesh_data->vertices.size());

        if (mesh_data->collision_data != nullptr) {
            m_collisions_data = std::unique_ptr<CollisionData>(mesh_data->collision_data.release());
            m_bounding_box = math::AABB { m_collisions_data->max };
        } else {
            m_collisions_data = std::make_unique<CollisionData>();
            std::copy(mesh_data->vertices.begin(), mesh_data->vertices.end(), m_collisions_data->vertices.data());

            m_bounding_box = math::AABB { mesh_data->max };
        }
    }

    Mesh::Mesh(MeshData *mesh_data) {
        // TODO remove duplication
        buffer_array.set_data(0, sizeof(Vertex) * mesh_data->vertices.size(), mesh_data->vertices.data());
        vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        vertex_buffer.add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        vertex_buffer.add_vertex_attribute({2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true});

        m_gl_size = static_cast<int>(mesh_data->vertices.size());
    }
}

