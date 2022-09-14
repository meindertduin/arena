#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"
#include "../assets/cache.h"

#include "component.h"

namespace entity {
    struct EcStaticMeshRenderer : public Component<EcStaticMeshRenderer> {
    public:
        graphics::Material *material = nullptr;
        std::shared_ptr<graphics::GpuTexture> texture;
        std::shared_ptr<graphics::Mesh> mesh;

        EcStaticMeshRenderer() = default;

        void init(const std::string& filename);
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
