#pragma once

#include <cstdint>
#include "../entity/ec_transform.h"

#include "gpu_buffer.h"

namespace graphics {
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::u16vec2 textcoords;
    };

    struct MeshData {
        std::vector<Vertex> vertices;
    };

    struct Mesh {
    public:
        Mesh(MeshData *mesh_data);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void render() const;
        entity::ECTransform transform;
    private:
        std::size_t size;
        VertexBuffer vertex_buffer { sizeof(Vertex) };
        ArrayBuffer buffer_array;
    };
}

