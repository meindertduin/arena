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
        graphics::Texture *texture = nullptr;
        assets::AssetHandle<graphics::Mesh> mesh;

        EcStaticMeshRenderer() = default;

        void init(std::string filename);
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
