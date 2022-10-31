#pragma once

#include <glm/vec3.hpp>
#include "../entity/ec_transform.h"
#include "../graphics/mesh.h"

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

        [[nodiscard]] virtual glm::vec3 find_furthest_points(const glm::vec3 &direction) const = 0;
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

        [[nodiscard]] glm::vec3 find_furthest_points(const glm::vec3 &direction) const override { };
    };

    class MeshCollider : public Collider {
    public:
        CollisionPoints test(
                const Transform &transform,
                const Collider* collider,
                const Transform &collider_transform) const override;

        CollisionPoints test(
                const Transform &transform,
                const SphereCollider* collider,
                const Transform &sphere_transform) const override;

        [[nodiscard]] glm::vec3 find_furthest_points(const glm::vec3 &direction) const override;
    private:
        std::shared_ptr<graphics::Mesh> m_mesh;
    };

    inline glm::vec3 support(const Collider *c_a, const Collider *c_b, const glm::vec3 &direction);

    class Simplex {
    public:
        Simplex() :
            m_points({ glm::vec3{0}, glm::vec3{0}, glm::vec3{0}, glm::vec3{0} }),
            m_size{0}
        {}

        Simplex& operator=(std::initializer_list<glm::vec3> list) {
            for (auto v = list.begin(); v != list.end(); v++) {
                m_points[std::distance(list.begin(), v)] = *v;
            }

            m_size = list.size();

            return *this;
        }

        void push_front(const glm::vec3 &point) {
            m_points = { point, m_points[0], m_points[1], m_points[2] };
            m_size = std::min(m_size + 1, 4u);
        }

        constexpr ALWAYS_INLINE glm::vec3& operator[](uint32_t i) { return m_points[i]; }
        [[nodiscard]] constexpr ALWAYS_INLINE uint32_t size() const { return m_size; }

        [[nodiscard]] constexpr auto begin() const { return m_points.begin(); }
        [[nodiscard]] constexpr auto end() const { return m_points.end(); }
    private:
        std::array<glm::vec3, 4> m_points;
        uint32_t m_size;
    };
 }