#include "mesh.h"

#include <glad/glad.h>

#include <utility>

namespace graphics {
    void Mesh::render() const {
        this->m_array_buffer->bind();

        this->m_vertex_buffer->bind();
        glDrawArrays(GL_TRIANGLES, 0, m_gl_size);
    }

    Mesh::Mesh(MeshData *mesh_data) {
        init(mesh_data);
    }

    Mesh::Mesh(MeshData* mesh_data, std::shared_ptr<Material> material) : m_material{std::move(material)} {
        init(mesh_data);
    }

    void Mesh::init(MeshData *mesh_data) {
        m_vertex_buffer = std::make_shared<VertexBuffer>(sizeof(Vertex));
        m_array_buffer = std::make_shared<ArrayBuffer>();

        m_array_buffer->set_data(0, sizeof(Vertex) * mesh_data->vertices.size(), mesh_data->vertices.data());
        m_vertex_buffer->add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        m_vertex_buffer->add_vertex_attribute({3, GL_FLOAT, sizeof(float), false});
        m_vertex_buffer->add_vertex_attribute({2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true});

        m_gl_size = static_cast<int>(mesh_data->vertices.size());

        if (mesh_data->collision_data != nullptr) {
            m_collisions_data = std::unique_ptr<CollisionData>(mesh_data->collision_data.release());
        } else {
            m_collisions_data = std::make_unique<CollisionData>();
            m_collisions_data->vertices.reserve(mesh_data->vertices.size());
            std::copy(mesh_data->vertices.begin(), mesh_data->vertices.end(), &m_collisions_data->vertices[0]);
        }
    }
}

