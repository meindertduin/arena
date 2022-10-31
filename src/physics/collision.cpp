#include "collision.h"

namespace physics {
    inline CollisionPoints find_sphere_sphere_collision(const SphereCollider *a, const Transform &ta, const SphereCollider* b, const Transform &tb) {
        CollisionPoints result{};
        auto distance = glm::distance(a->center, b->center);
        auto radius_sum = a->radius + b->radius;

        if (distance > radius_sum) {
            return result;
        }

        glm::vec3 ab = a->center - b->center;
        result.furthest_a = ((a->radius / distance) * ab) + a->center;
        result.furthest_a = ((b->radius / distance) * -ab) + b->center;
        result.normal = glm::normalize(result.furthest_b - result.furthest_a);
        result.has_collision = true;
        result.depth = radius_sum - distance;

        return result;
    }

    CollisionPoints SphereCollider::test(const Transform &transform, const Collider *collider, const Transform &collider_transform) const {
        return collider->test(collider_transform, this, transform);
    }

    CollisionPoints SphereCollider::test(const Transform &transform, const SphereCollider *collider, const Transform &sphere_transform) const {
        return find_sphere_sphere_collision(this, transform, collider, sphere_transform);
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const Collider *collider,
                                       const Transform &collider_transform) const {
        return { };
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const SphereCollider *collider,
                                       const Transform &sphere_transform) const {
        return { };
    }

    glm::vec3 MeshCollider::find_furthest_points(const glm::vec3 &direction) const {
        glm::vec3 max_point;

        float max_distance = -FLT_MAX;
        return max_point;
    }
}