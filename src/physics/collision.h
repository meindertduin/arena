#pragma once

#include <glm/vec3.hpp>
#include "../entity/ec_transform.h"
#include "../graphics/mesh.h"
#include "../entity/ec_collision.h"

namespace physics {
    using Transform = entity::ECTransform;

    struct CollisionPoints {
        glm::vec3 furthest_a;
        glm::vec3 furthest_b;
        glm::vec3 normal;
        float depth;
        bool has_collision;
    };

    struct Collision {
        entity::Entity entity_a;
        entity::Entity entity_b;
        Transform *transform_a;
        Transform *transform_b;
        CollisionPoints points;
    };

    class Collider;
    class SphereCollider;
    class MeshCollider;

    enum class ColliderType {
        Sphere,
        Mesh,
    };

    class Collider {
    public:
        explicit Collider(ColliderType collider_type) :
            m_type{collider_type}
        {}

        virtual ~Collider() = default;

        [[nodiscard]] virtual glm::vec3 find_furthest_points(const glm::vec3 &direction, const Transform &transform) const = 0;
        [[nodiscard]] constexpr ColliderType type() const { return m_type; }

        CollisionPoints test_collision(const Transform &transform, Collider *collider, const Transform &other_transform) const {
            switch (collider->type()) {
                case ColliderType::Sphere:
                    return this->test(transform, reinterpret_cast<SphereCollider*>(collider), other_transform);
                case ColliderType::Mesh:
                    return this->test(transform, reinterpret_cast<MeshCollider*>(collider), other_transform);
            }
        }
    protected:
        virtual CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &collider_transform) const = 0;

        virtual CollisionPoints test(
                const Transform &transform,
                const MeshCollider* collider,
                const Transform &collider_transform) const = 0;

    private:
        const ColliderType m_type;
    };

    class SphereCollider : public Collider {
    public:
        glm::vec3 center;
        float radius;

        SphereCollider(ColliderType type) : Collider(type) {}

        [[nodiscard]] glm::vec3 find_furthest_points(const glm::vec3 &direction, const Transform &transform) const override { };
    protected:
        CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &sphere_transform) const override;

        CollisionPoints test(
                const Transform &transform,
                const MeshCollider* collider,
                const Transform &sphere_transform) const override;

    };

    class MeshCollider : public Collider {
    public:
        explicit MeshCollider(ColliderType type, std::shared_ptr<graphics::MeshData> mesh_data)
            : Collider(type),
            m_mesh_data{std::move(mesh_data)}
        {}

        [[nodiscard]] glm::vec3 find_furthest_points(const glm::vec3 &direction, const Transform &transform) const override;
    protected:
        CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &sphere_transform) const override;

        CollisionPoints test(
                const Transform &transform,
                const MeshCollider* collider,
                const Transform &sphere_transform) const override;

    private:
        std::shared_ptr<graphics::MeshData> m_mesh_data;
    };
 }