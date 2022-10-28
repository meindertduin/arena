#pragma once

#include <glm/vec3.hpp>
#include "../entity/ec_transform.h"

namespace physics {
    using Transform = entity::ECTransform;

    struct CollisionPoints {
        glm::vec3 furthest_a;
        glm::vec3 furthest_b;
        glm::vec3 normal;
        float depth;
        bool has_collision;
    };

    class Collider;
    class SphereCollider;

    class Collider {
    public:
        virtual CollisionPoints test(
                const Transform &transform,
                const Collider* collider,
                const Transform &collider_transform) const = 0;

        virtual CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &collider_transform) const = 0;
    };

    class SphereCollider : public Collider {
    public:
        glm::vec3 center;
        float radius;

        CollisionPoints test(
                const Transform &transform,
                const Collider* collider,
                const Transform &collider_transform) const override;

        CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &sphere_transform) const override;
    };
}