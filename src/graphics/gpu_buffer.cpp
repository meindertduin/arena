#include "gpu_buffer.h"
#include "shader.h"

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
        std::size_t size = 0;
        for (int i = 0; i < vertex_attributes.size(); i++) {
            const auto &attribute = vertex_attributes[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.amount, attribute.type, attribute.normalized ? GL_TRUE : GL_FALSE, total_size, (void*) size);

            size += attribute.amount * attribute.size_type;
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

    SharedDataBuffer::SharedDataBuffer(int binding_block, std::size_t size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
  
        // define the range of the buffer that links to a uniform binding point
        glBindBufferRange(GL_UNIFORM_BUFFER, binding_block, id, 0, size);
  
        this->size = size;
    }

    SharedDataBuffer::~SharedDataBuffer() {
        glDeleteBuffers(1, &id);
    }

    void SharedDataBuffer::set_data(int format_size, std::size_t size, const void *data) {
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
        offset += format_size;
    }

    void SharedDataBuffer::reset() {
        offset = 0;
    }

    void SharedDataBuffer::set_offset(int offset) {
        this->offset = offset;
    }

    void SharedDataBuffer::bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
    }

    void SharedDataBuffer::unbind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    UniformBuffer::UniformBuffer(const std::string &uniform_name, const Uniform &uniform, const ShaderProgram &program) {
        m_name = uniform_name;
        m_size = uniform.size();

        glGenBuffers(1, &id);
        glBindBuffer(GL_UNIFORM_BUFFER, id);
        glBufferData(GL_UNIFORM_BUFFER, m_size, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        // define the range of the buffer that links to a uniform binding point
        m_uniform_index = glGetUniformLocation(program.id(), uniform_name.c_str());
        glBindBufferRange(GL_UNIFORM_BUFFER, m_uniform_index, id, 0, m_size);
    }

    UniformBuffer::~UniformBuffer() {
        glDeleteBuffers(1, &id);
    }

    void UniformBuffer::bind() const {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
    }

    void UniformBuffer::reset() {
        m_offset = 0;
    }

    void UniformBuffer::set_data(const Uniform &uniform) {
        glad_glBufferSubData(GL_UNIFORM_BUFFER, m_offset, uniform.size(), &uniform.value);
        m_offset += uniform.size();
    }
}