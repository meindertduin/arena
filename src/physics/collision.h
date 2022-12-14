#pragma once

#include <glm/vec3.hpp>
#include "../entity/ec_transform.h"
#include "../graphics/mesh.h"
#include "../entity/ec_rigid_body.h"
#include "../graphics/model.h"

namespace physics {
    using Transform = entity::ECTransform;
    class PhysicsObject;

    struct CollisionPoints {
        glm::vec3 furthest_a;
        glm::vec3 furthest_b;
        glm::vec3 normal;
        float depth;
        bool has_collision;
    };

    struct Collision {
        entity::ECRigidBody *collision_object_a;
        entity::CollisionObject *collision_object_b;
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
        explicit Collider(ColliderType collider_type, const std::shared_ptr<graphics::Model> &model) :
            m_type{collider_type},
            m_aabb{model->aabb()}
        {}

        virtual ~Collider() = default;

        [[nodiscard]] virtual glm::vec3 find_furthest_points(const glm::vec3 &direction, const Transform &transform) const = 0;
        [[nodiscard]] constexpr ColliderType type() const { return m_type; }

        constexpr ALWAYS_INLINE math::AABB& aabb() { return m_aabb; }
        constexpr ALWAYS_INLINE math::AABB& aabb(const Transform& transform) { return m_aabb; }

        CollisionPoints test_collision(const Transform &transform, Collider *collider, const Transform &other_transform);
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
        math::AABB m_aabb;
    };

    class SphereCollider : public Collider {
    public:
        glm::vec3 center{};
        float radius{};

        explicit SphereCollider(const std::shared_ptr<graphics::Model> &model) : Collider(ColliderType::Sphere, model) {}

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
        explicit MeshCollider(const std::shared_ptr<graphics::Model> &model);

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
        std::shared_ptr<graphics::CollisionData> m_mesh_data;
    };
 }