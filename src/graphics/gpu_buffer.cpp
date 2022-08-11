#include "gpu_buffer.h"

#include <glad/glad.h>
#include <stdexcept>

namespace graphics {
    ArrayBuffer::ArrayBuffer() {
        glGenBuffers(1, &id);
    }

    ArrayBuffer::~ArrayBuffer() {
        glDeleteBuffers(1, &id);
    }

    void ArrayBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void ArrayBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ArrayBuffer::set_data(int offset, std::size_t size, const void *data) {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(int total_size) {
        glGenVertexArrays(1, &id);

        this->total_size = total_size;
        this->current_size = 0;
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteVertexArrays(1, &id);
    }

    void VertexBuffer::bind() const {
        glBindVertexArray(id);

        std::size_t currentSize = 0;
        for (int i = 0; i < vertex_attributes.size(); i++) {
            const auto &attribute = vertex_attributes[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.amount, attribute.type, attribute.normalized ? GL_TRUE : GL_FALSE, total_size, (void*) currentSize);

            currentSize += attribute.amount * attribute.size_type;
        }
    }

    void VertexBuffer::unbind() const {
        glEnableVertexAttribArray(0);
    }

    void VertexBuffer::add_vertex_attribute(const VertexAttribute &attribute) {
        auto to_add_size = attribute.size_type * attribute.amount;

        if (to_add_size + current_size > total_size) {
            throw std::runtime_error("Runtime Error: Adding extra attribute to the VertexArray will exceed the total size.");
        }

        current_size += to_add_size;
        vertex_attributes.push_back(attribute);
    }
}