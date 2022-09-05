#include "mesh.h"

#include <memory>
#include <glad/glad.h>
#include "../assets/obj_loader.h"

namespace graphics {
    Mesh::Mesh(MeshData *mesh_data) {
        this->buffer_array.set_data(0, sizeof(Vertex) * mesh_data->vertices.size(), mesh_data->vertices.data());
        this->vertex_buffer.add_vertex_attribute({ 3, GL_FLOAT, sizeof(float), false });
        this->vertex_buffer.add_vertex_attribute({ 3, GL_FLOAT, sizeof(float), false });
        this->vertex_buffer.add_vertex_attribute({ 2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true });

        this->size = mesh_data->vertices.size();
    }

    void Mesh::render() const {
        this->buffer_array.bind();

        // TODO binding new vertex array and setting the vertex-attributes is quite expensive
        this->vertex_buffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, this->size);
    }
}

