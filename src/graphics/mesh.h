#pragma once

#include <cstdint>
#include "../entity/ec_transform.h"

#include "gpu_buffer.h"
#include "../math/box.h"
#include "../assets/resource.h"
#include "material.h"

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

    class Mesh : public IRenderAble {
    public:
        explicit Mesh(MeshData* mesh_data);
        void render() const override;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<Material>& material() const {
            return m_material;
        }
        void set_material(const std::shared_ptr<Material> &material) { m_material = material; }

        entity::ECTransform transform;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<CollisionData>& collisions_data() const {
            return m_collisions_data;
        }
    private:
        std::shared_ptr<VertexBuffer> m_vertex_buffer;
        std::shared_ptr<ArrayBuffer> m_array_buffer;
        std::shared_ptr<Material> m_material;

        int m_gl_size {0};

        std::shared_ptr<CollisionData> m_collisions_data { nullptr };
    };
}