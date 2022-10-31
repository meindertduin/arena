#pragma once

#include <cstdint>
#include "../entity/ec_transform.h"

#include "gpu_buffer.h"
#include "../math/box.h"

namespace graphics {
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::u16vec2 textcoords;
    };

    struct Renderable {
        virtual void render() const = 0;
    };

    struct MeshData {
        float x_min;
        float x_max;
        float y_min;
        float y_max;
        float z_min;
        float z_max;

        std::vector<Vertex> vertices;
    };

    class Mesh : public Renderable {
    public:
        Mesh(MeshData *mesh_data, const math::AABB &box);
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void render() const override;
        void add_collision_data(MeshData *collision_data);

        entity::ECTransform transform;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<MeshData>& mesh_data() const { return m_mesh_data; }
        [[nodiscard]] constexpr ALWAYS_INLINE std::vector<std::shared_ptr<MeshData>> collisions_data() const { return m_collisions_data; }

        constexpr ALWAYS_INLINE math::AABB& bounding_box() { return m_bounding_box; }
    private:
        std::size_t size;

        VertexBuffer vertex_buffer { sizeof(Vertex) };
        ArrayBuffer buffer_array;
        math::AABB m_bounding_box {};

        std::shared_ptr<MeshData> m_mesh_data;
        std::vector<std::shared_ptr<MeshData>> m_collisions_data;
    };
}