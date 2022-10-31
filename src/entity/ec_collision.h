#pragma once

#include "component.h"
#include "../graphics/mesh.h"
#include "../physics/collision.h"

namespace entity {
    class ECCollision : public Component<ECCollision> {
    public:
        void init(const std::string &filename);
        constexpr ALWAYS_INLINE std::shared_ptr<graphics::Mesh>& mesh() { return mp_mesh; }
        constexpr ALWAYS_INLINE std::shared_ptr<physics::Collider>& collider() { return m_collider; }
    private:
        std::shared_ptr<graphics::Mesh> mp_mesh;
        std::shared_ptr<physics::Collider> m_collider;
    };

    DECL_COMPONENT_HEADER(ECCollision);
}

