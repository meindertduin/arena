#pragma once

#include "component.h"
#include "../graphics/mesh.h"
#include "../physics/collision.h"

namespace entity {
    class ECCollision : public Component<ECCollision> {
    public:
        ECCollision() = default;
        ECCollision(bool is_dynamic) :
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic}
        {}

        void init(const std::string &filename);
        constexpr ALWAYS_INLINE std::shared_ptr<graphics::Mesh>& mesh() { return mp_mesh; }
        constexpr ALWAYS_INLINE std::shared_ptr<physics::Collider>& collider() { return m_collider; }

        [[nodiscard]] constexpr ALWAYS_INLINE bool is_static() const { return m_is_static; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool is_dynamic() const { return m_is_dynamic; }
    private:
        std::shared_ptr<graphics::Mesh> mp_mesh;
        std::shared_ptr<physics::Collider> m_collider;
        bool m_is_static;
        bool m_is_dynamic;
    };

    DECL_COMPONENT_HEADER(ECCollision);
}

