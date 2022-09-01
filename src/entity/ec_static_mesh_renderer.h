#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"

#include "component.h"

namespace entity {
    struct EcStaticMeshRenderer : public Component<EcStaticMeshRenderer> {
    public:
        EcStaticMeshRenderer();
        graphics::Mesh *mesh;
        graphics::Material *material;
        graphics::Texture *texture;
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
