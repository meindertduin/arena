#include "collision.h"
#include "algorithm.h"

namespace physics {
    CollisionPoints Collider::test_collision(const Transform &transform, Collider *collider, const Transform &other_transform) {
        this->aabb().set_center(transform.pos);
        collider->aabb().set_center(other_transform.pos);

        if (!this->m_aabb.inside(collider->aabb()))
            return {};

        switch (collider->type()) {
            case ColliderType::Sphere:
                return this->test(transform, reinterpret_cast<SphereCollider*>(collider), other_transform);
            case ColliderType::Mesh:
                return this->test(transform, reinterpret_cast<MeshCollider*>(collider), other_transform);
        }
    }

    inline CollisionPoints
    find_sphere_sphere_collision(const SphereCollider *a, const Transform &ta, const SphereCollider *b,
                                 const Transform &tb) {
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

    CollisionPoints SphereCollider::test(const Transform &transform, const SphereCollider *collider,
                                         const Transform &sphere_transform) const {
        return find_sphere_sphere_collision(this, transform, collider, sphere_transform);
    }

    CollisionPoints SphereCollider::test(const Transform &transform, const MeshCollider *collider,
                                         const Transform &sphere_transform) const {
        return {};
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const SphereCollider *collider,
                                       const Transform &sphere_transform) const {
        return {};
    }

    glm::vec3 MeshCollider::find_furthest_points(const glm::vec3 &direction, const Transform &transform) const {
        glm::vec4 max_point;
        float max_distance = -FLT_MAX;
        auto transform_matrix = transform.get_transform_4x4();

        for (auto &vertex: m_mesh_data->vertices) {
            // TODO: use manual transforming and rotation calculation, instead of matrix multiplication
            auto world_pos = transform_matrix * glm::vec4(vertex.pos, 1.0f);
            float distance = glm::dot(world_pos, glm::vec4(direction, 1.0f));

            if (distance > max_distance) {
                max_distance = distance;
                max_point = world_pos;
            }
        }

        return max_point;
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const MeshCollider *collider,
                                       const Transform &mesh_transform) const {
        auto [collides, simplex] = gjk(this, collider, transform, mesh_transform);
        if (collides) {
            return epa(simplex, this, collider, transform, mesh_transform);
        }
        return {};
    }

    MeshCollider::MeshCollider(const std::shared_ptr<graphics::Mesh> &mesh) : Collider(ColliderType::Mesh, mesh) {
        this->m_mesh_data = mesh->collisions_data();
    }
}