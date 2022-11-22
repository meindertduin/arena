#pragma once

#include "../assets/resource.h"
#include "mesh.h"
#include "material.h"

namespace graphics {
    class Model : public assets::Resource {
    public:
        void render();

        void load(std::size_t size, char *data) override;
        void unload() override { }

        [[nodiscard]] constexpr ALWAYS_INLINE const math::AABB& aabb() const { return m_aabb; }
    protected:
        explicit Model(const Path &path) : Resource(path) {}
    private:
        std::vector<Mesh> m_meshes;

        math::AABB m_aabb {};
    };
}