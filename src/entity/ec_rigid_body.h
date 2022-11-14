#pragma once

#include "component.h"
#include "../graphics/mesh.h"

namespace physics {
    class Collider;
}

namespace entity {
    class ECRigidBody : public Component<ECRigidBody> {
    public:
        ECRigidBody(bool is_dynamic) :
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic}
        {}

        constexpr ALWAYS_INLINE std::shared_ptr<physics::Collider>& collider() { return m_collider; }
        void set_collider(std::shared_ptr<physics::Collider> &&collider) { m_collider = collider; }

        [[nodiscard]] constexpr ALWAYS_INLINE bool is_static() const { return m_is_static; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool is_dynamic() const { return m_is_dynamic; }
    private:
        std::shared_ptr<physics::Collider> m_collider;

        bool m_is_static { false };
        bool m_is_dynamic { false };
    };

    DECL_COMPONENT_HEADER(ECRigidBody);
}

