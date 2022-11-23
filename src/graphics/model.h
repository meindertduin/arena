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
        void render();

        void load(std::size_t size, char *data) override;
        void unload() override { }

        [[nodiscard]] constexpr ALWAYS_INLINE const math::AABB& aabb() const { return m_aabb; }
    private:
        // TODO, have the meshes on the stack
        std::vector<std::unique_ptr<Mesh>> m_meshes;
        math::AABB m_aabb {};
    };
}