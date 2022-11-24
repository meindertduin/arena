#pragma once

#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"
#include "../assets/cache.h"

#include "component.h"

namespace entity {
    class ECStaticModel : public Component<ECStaticModel> {
    public:
        explicit ECStaticModel(std::shared_ptr<graphics::Model> model) :
            Component(),
            m_model{std::move(model)}
        {}

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<graphics::Model>& model() const { return m_model; }
    private:
        std::shared_ptr<graphics::Model> m_model;
    };

    DECL_COMPONENT_HEADER(ECStaticModel);
}
