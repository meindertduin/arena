#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"

#include "component.h"

namespace entity {
    struct EcStaticMeshRenderer : public Component<EcStaticMeshRenderer> {
    public:
        graphics::Mesh *mesh = nullptr;
        graphics::Material *material = nullptr;
        graphics::Texture *texture = nullptr;

        EcStaticMeshRenderer() = default;

        void init(std::string filename);
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
