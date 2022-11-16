#pragma once

#include "../platform/platform.h"
#include "component.h"
#include "ec_transform.h"


namespace physics {
    class Collider;
    class CollisionPoints;
}

namespace entity {
    class ECCollisionObject : public Component<ECCollisionObject> {
    public:
        explicit ECCollisionObject(bool is_dynamic, ECTransform *transform) : Component(),
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic},
            m_transform{transform}
        {}

        ECCollisionObject(bool detect_collisions, bool is_dynamic, ECTransform *transform) : Component(),
            m_detect_collisions{detect_collisions},
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic},
            m_transform{transform}
        {}

        constexpr ALWAYS_INLINE const std::shared_ptr<physics::Collider>& collider() const { return m_collider; }
        void set_collider(std::shared_ptr<physics::Collider> &&collider) { m_collider = collider; }

        [[nodiscard]] constexpr ALWAYS_INLINE bool is_static() const { return m_is_static; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool is_dynamic() const { return m_is_dynamic; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool detect_collisions() const { return m_detect_collisions; }
        [[nodiscard]] constexpr ALWAYS_INLINE ECTransform* transform() const { return m_transform; }

        [[nodiscard]] physics::CollisionPoints test_collision(const ECCollisionObject &other);
    private:
        std::shared_ptr<physics::Collider> m_collider;

        bool m_is_static { false };
        bool m_is_dynamic { false };
        bool m_detect_collisions { true };

        ECTransform *m_transform { nullptr };
    };

    DECL_COMPONENT_HEADER(ECCollisionObject);
}