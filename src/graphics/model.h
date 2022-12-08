#pragma once

#include "../assets/resource.h"
#include "mesh.h"
#include "material.h"

namespace graphics {

    struct ModelData {
        std::vector<MeshData*> meshes;
    };

    class Model : public assets::Resource {
    public:
        explicit Model(const Path &path) : Resource(path) {}

        [[nodiscard]] constexpr ALWAYS_INLINE const math::AABB& aabb() const {
            return m_aabb;
        }

        [[nodiscard]] const std::shared_ptr<CollisionData>& collision_data() const {
            // TODO have one collision data that lives in the model
            return m_meshes[0].collisions_data();
        }

        [[nodiscard]] constexpr ALWAYS_INLINE const std::vector<Mesh>& meshes() const { return m_meshes; }
    protected:
        friend class assets::Cache;

        void load() override;
    private:
        std::vector<Mesh> m_meshes;
        math::AABB m_aabb {};

        std::shared_ptr<CollisionData> m_collisions_data { nullptr };
    };
}