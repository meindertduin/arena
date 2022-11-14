#pragma once

#include "../entity/entity.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_rigid_body.h"
#include "collision.h"

#include <optional>

namespace physics {
    using Transform = entity::ECTransform;
    using RigidBody = entity::ECRigidBody;

    class PhysicsObject  {
    public:
        explicit PhysicsObject(entity::Entity entity) : m_entity{entity} {
            m_transform = &entity.get<Transform>();
            m_rigid_body = &entity.get<RigidBody>();
        }

        [[nodiscard]] constexpr ALWAYS_INLINE Transform* transform() const {
            return m_transform;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE RigidBody* rigid_body() const {
            return m_rigid_body;
        }

        [[nodiscard]] CollisionPoints test_collision(const PhysicsObject &other) const;
    private:
        entity::Entity m_entity;
        Transform *m_transform;
        RigidBody *m_rigid_body;
    };
}