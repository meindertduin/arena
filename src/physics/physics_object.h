#pragma once

#include "../entity/entity.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_rigid_body.h"
#include "../entity/ec_physics.h"
#include "collision.h"

#include <optional>

namespace physics {
    using Transform = entity::ECTransform;
    using RigidBody = entity::ECRigidBody;
    using Physics = entity::ECPhysics;

    class PhysicsObject  {
    public:
        explicit PhysicsObject(entity::Entity entity) : m_entity{entity} {
            m_transform = &entity.get<Transform>();
            m_rigid_body = &entity.get<RigidBody>();
            m_physics = entity.get_opt<Physics>();
        }

        [[nodiscard]] constexpr ALWAYS_INLINE entity::Entity entity() const {
            return m_entity;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE Transform* transform() const {
            return m_transform;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE RigidBody* rigid_body() const {
            return m_rigid_body;
        }

        [[nodiscard]] constexpr ALWAYS_INLINE std::optional<Physics*> physics() const {
            return m_physics;
        }

        [[nodiscard]] CollisionPoints test_collision(const PhysicsObject &other) const;
    private:
        entity::Entity m_entity;
        Transform *m_transform;
        RigidBody *m_rigid_body;
        std::optional<entity::ECPhysics*> m_physics = std::nullopt;
    };
}