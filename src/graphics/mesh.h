#pragma once

#include <stdint.h>
#include "../entity/transform.h"

#include "gpu_buffer.h"

namespace graphics {
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 textcoords;
    };

    struct MeshData {
        std::vector<Vertex> vertices;
    };

    struct Mesh {
    public:
        Mesh();
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) = delete;

        void render();
        entity::Transform transform;
    private:
        VertexBuffer vertex_buffer { 8 * sizeof(float) };
        ArrayBuffer buffer_array;
    };
}

