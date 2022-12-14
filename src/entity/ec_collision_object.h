#pragma once

#include "../platform/platform.h"
#include "component.h"
#include "ec_transform.h"

namespace physics {
    class Collider;
    class CollisionPoints;
}

namespace entity {
    class CollisionObject {
    public:
        explicit CollisionObject(bool is_dynamic, ECTransform *transform) :
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic},
            mp_transform{transform}
        {}

        CollisionObject(bool detect_collisions, bool is_dynamic, ECTransform *transform) :
            m_detect_collisions{detect_collisions},
            m_is_dynamic{is_dynamic},
            m_is_static{!is_dynamic},
            mp_transform{transform}
        {}

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<physics::Collider>& collider() const { return m_collider; }
        void set_collider(std::shared_ptr<physics::Collider> &&collider) { m_collider = collider; }

        [[nodiscard]] constexpr ALWAYS_INLINE bool is_static() const { return m_is_static; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool is_dynamic() const { return m_is_dynamic; }
        [[nodiscard]] constexpr ALWAYS_INLINE bool detect_collisions() const { return m_detect_collisions; }

        [[nodiscard]] constexpr ALWAYS_INLINE const entity::ECTransform* transform() const { return mp_transform; }
        [[nodiscard]] constexpr ALWAYS_INLINE entity::ECTransform* transform() { return mp_transform; }

        [[nodiscard]] physics::CollisionPoints test_collision(const CollisionObject *other);
    protected:
        entity::ECTransform *mp_transform { nullptr };
    private:
        std::shared_ptr<physics::Collider> m_collider;

        bool m_is_static { false };
        bool m_is_dynamic { false };
        bool m_detect_collisions { true };
    };

    class ECCollisionObject : public Component<ECCollisionObject>, public CollisionObject {
    public:
        explicit ECCollisionObject(bool is_dynamic, ECTransform *transform) :
            CollisionObject(is_dynamic, transform),
            Component<ECCollisionObject>()
        {}

        ECCollisionObject(bool detect_collisions, bool is_dynamic, ECTransform *transform) :
            CollisionObject(detect_collisions, is_dynamic, transform),
            Component<ECCollisionObject>()
        {}
    };

    DECL_COMPONENT_HEADER(ECCollisionObject);
}