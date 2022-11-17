#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"
#include "../assets/cache.h"

#include "component.h"

namespace entity {
    class EcStaticMeshRenderer : public Component<EcStaticMeshRenderer> {
    public:
        explicit EcStaticMeshRenderer(std::shared_ptr<graphics::Mesh> mesh, std::shared_ptr<graphics::Material> material) :
            Component(),
            mesh{std::move(mesh)},
            material{std::move(material)}
        {}

        std::shared_ptr<graphics::Material> material;
        std::shared_ptr<graphics::Mesh> mesh;
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
