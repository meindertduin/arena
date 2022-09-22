#include "geometry.h"

#include <glad/glad.h>

namespace graphics {
    GpuPlane::GpuPlane() {
        this->array_buffer.set_data(0, sizeof(Vertex) * 6, vertices);
        this->vertex_buffer.add_vertex_attribute({ 2, GL_FLOAT, sizeof(float), false });
        this->vertex_buffer.add_vertex_attribute({ 2, GL_UNSIGNED_SHORT, sizeof(uint16_t), true });
    }

    void GpuPlane::render() {
        this->array_buffer.bind();
        this->vertex_buffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}