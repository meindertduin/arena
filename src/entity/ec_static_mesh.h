#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"
#include "../assets/cache.h"

#include "component.h"

namespace entity {
    class EcStaticMeshRenderer : public Component<EcStaticMeshRenderer> {
    public:
        explicit EcStaticMeshRenderer(std::shared_ptr<graphics::Model> model) :
            Component(),
            m_model{std::move(model)}
        {}

        std::shared_ptr<graphics::Model> m_model;
    };

    DECL_COMPONENT_HEADER(EcStaticMeshRenderer);
}
