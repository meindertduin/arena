#pragma once

#include <cstdint>
#include "../entity/ec_transform.h"

#include "gpu_buffer.h"
#include "../math/box.h"
#include "../assets/resource.h"

namespace graphics {
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::u16vec2 textcoords;
    };

    struct IRenderAble {
        virtual void render() const = 0;
    };

    struct CollisionData {
        float max;
        std::vector<Vertex> vertices;
    };

    struct MeshData {
        float max;
        std::vector<Vertex> vertices;
        std::unique_ptr<CollisionData> collision_data { nullptr };
    };

    class Mesh : public IRenderAble, public assets::Resource {
    public:
        explicit Mesh(const Path &path) : assets::Resource(path) {}
        explicit Mesh(MeshData* mesh_data);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void render() const override;

        entity::ECTransform transform;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<CollisionData>& collisions_data() const {
            return m_collisions_data;
        }

        constexpr ALWAYS_INLINE math::AABB& bounding_box() { return m_bounding_box; }

        void load(std::size_t size, char *data) override;
        void unload() override { }
    private:
        VertexBuffer vertex_buffer { sizeof(Vertex) };
        ArrayBuffer buffer_array;
        math::AABB m_bounding_box {};

        int m_gl_size {0};

        std::shared_ptr<CollisionData> m_collisions_data { nullptr };
    };
}