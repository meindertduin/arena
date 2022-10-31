#include "collision.h"

namespace physics {
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

    CollisionPoints SphereCollider::test(const Transform &transform, const Collider *collider,
                                         const Transform &collider_transform) const {
        return collider->test(collider_transform, this, transform);
    }

    CollisionPoints SphereCollider::test(const Transform &transform, const SphereCollider *collider,
                                         const Transform &sphere_transform) const {
        return find_sphere_sphere_collision(this, transform, collider, sphere_transform);
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const Collider *collider,
                                       const Transform &collider_transform) const {
        return {};
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const SphereCollider *collider,
                                       const Transform &sphere_transform) const {
        return {};
    }

    glm::vec3 MeshCollider::find_furthest_points(const glm::vec3 &direction) const {
        glm::vec3 max_point;
        float max_distance = -FLT_MAX;
        auto &mesh_data = m_mesh->mesh_data();

        for (auto &vertex: mesh_data->vertices) {
            float distance = glm::dot(vertex.pos, direction);
            if (distance > max_distance) {
                max_distance = distance;
                max_point = vertex.pos;
            }
        }

        return max_point;
    }

    inline glm::vec3 support(const Collider *c_a, const Collider *c_b, const glm::vec3 &direction) {
        return c_a->find_furthest_points(direction) - c_b->find_furthest_points(-direction);
    }

    bool gjk(const Collider *c_a, const Collider *c_b) {
        auto sup = support(c_a, c_b, glm::vec3{1, 0, 0});
        Simplex points;
        points.push_front(sup);

        // new direction is towards the origin
        glm::vec3 direction = -sup;

        while (true) {
            sup = support(c_a, c_b, direction);

            if (glm::dot(sup, direction) <= 0) {
                return false; // no collsion
            }

            points.push_front(sup);

            if (next_simples(points, direction)) {
                return true;
            }
        }
    }

    inline bool next_simples(Simplex &points, glm::vec3 &direction) {
        switch (points.size()) {
            case 2: return line(points, direction);
            case 3: return triangle(points, direction);
            case 4: return tetrahedron(points, direction);
        }
        return false;
    }

    inline bool same_direction(const glm::vec3 &direction, const glm::vec3 &ao) {
        return glm::dot(direction, ao) > 0;
    }

    inline bool line(Simplex &points, glm::vec3& direction) {
        auto a = points[0];
        auto b = points[1];

        auto ab = b - a;
        auto ao = -a;

        if (same_direction(ab, ao)) {
            direction = glm::cross(glm::cross(ab, ao), ab);
        } else {
            points = { a };
            direction = ao;
        }

        return false;
    }

    inline bool triangle(Simplex &points, glm::vec3 &direction) {
        auto a = points[0];
        auto b = points[1];
        auto c = points[2];

        auto ab = b - a;
        auto ac = c - a;
        auto ao = -a;

        auto abc = glm::cross(ab, ac);

        if (same_direction(glm::cross(abc, ac), ao)) {
            if (same_direction(ac, ao)) {
                points = { a, c };
                direction = glm::cross(glm::cross(ac, ao), ac);
            } else {
                return line(points = { a, b }, direction);
            }
        } else {
            if (same_direction(glm::cross(ab, abc), ao)) {
                return line(points = { a, b }, direction);
            } else {
                if (same_direction(abc, ao)) {
                    direction = abc;
                } else {
                    points = { a, b, c };
                    direction = -abc;
                }
            }
        }

        return false;
    }

    inline bool tetrahedron(Simplex &points, glm::vec3 &direction) {
        auto a = points[0];
        auto b = points[1];
        auto c = points[2];
        auto d = points[3];

        auto ab = b - a;
        auto ac = c - a;
        auto ad = d - a;
        auto ao = -a;

        auto abc = glm::cross(ab, ac);
        auto acd = glm::cross(ac, ad);
        auto adb = glm::cross(ad, ab);

        if (same_direction(abc, ao)) {
            return triangle(points = { a, b, c }, direction);
        }

        if (same_direction(acd, ao)) {
            return triangle(points = { a, c, d }, direction);
        }

        if (same_direction(adb, ao)) {
            return triangle(points = { a, d, b }, direction);
        }

        return true;
    }
}