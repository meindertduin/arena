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

    CollisionPoints SphereCollider::test(const Transform &transform, const MeshCollider *collider,
                                         const Transform &sphere_transform) const {
        return {};
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

        for (auto &vertex: m_mesh_data->vertices) {
            float distance = glm::dot(vertex.pos, direction);
            if (distance > max_distance) {
                max_distance = distance;
                max_point = vertex.pos;
            }
        }

        return max_point;
    }

    CollisionPoints MeshCollider::test(const Transform &transform, const MeshCollider *collider,
                                       const Transform &mesh_transform) const {
        CollisionPoints collision{};
        collision.has_collision = gjk(this, collider, transform, mesh_transform);
        return collision;
    }

    inline glm::vec3 support(const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b, const glm::vec3 &direction) {
        return (c_a->find_furthest_points(direction) + t_a.pos) - (c_b->find_furthest_points(-direction) + t_b.pos);
    }

    bool gjk(const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b) {
        auto sup = support(c_a, c_b, t_a, t_b, glm::vec3{1, 0, 0});

        Simplex points;
        points.push_front(sup);

        // new direction is towards the origin
        glm::vec3 direction = -sup;

        while (true) {
            sup = support(c_a, c_b, t_a, t_b, direction);

            if (glm::dot(sup, direction) <= 0) {
                return false; // no collsion
            }

            points.push_front(sup);

            if (next_simplex(points, direction)) {
                return true;
            }
        }
    }

    CollisionPoints epa(const Simplex &simplex, const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b) {
        std::vector<glm::vec3> polytope(simplex.begin(), simplex.end());
        std::vector<size_t> faces = {
            0, 1, 2,
            0, 3, 1,
            0, 2, 3,
            1, 3, 2
        };

        auto [normals, min_face] = get_face_normals(polytope, faces);

        glm::vec3 min_normal;
        float min_distance = FLT_MAX;

        while (min_distance == FLT_MAX) {
            min_normal = glm::vec3{normals[min_face].x, normals[min_face].y, normals[min_face].z};
            min_distance = normals[min_face].w;

            auto sup = support(c_a, c_b, t_a, t_b, min_normal);
            float s_distance = glm::dot(min_normal, sup);

            if (std::abs(s_distance- min_distance) > 0.001f) {
                min_distance = FLT_MAX;
                std::vector<std::pair<size_t, size_t>> unique_edges;

                for (size_t i = 0; i < normals.size(); i++) {
                    if (same_direction(normals[i], sup)) {
                        auto f = i * 3;

                        add_if_unique_edge(unique_edges, faces, f    , f + 1);
                        add_if_unique_edge(unique_edges, faces, f + 1, f + 2);
                        add_if_unique_edge(unique_edges, faces, f + 2, f    );

                        faces[f + 2] = faces.back(); faces.pop_back();
                        faces[f + 1] = faces.back(); faces.pop_back();
                        faces[f    ] = faces.back(); faces.pop_back();

                        normals[i] = normals.back(); normals.pop_back();

                        i--;
                    }
                }

                std::vector<size_t> new_faces;
                for (auto [edge_index_1, edge_index_2] : unique_edges) {
                    new_faces.push_back(edge_index_1);
                    new_faces.push_back(edge_index_2);
                    new_faces.push_back(polytope.size());
                }

                polytope.push_back(sup);

                auto [new_normals, new_min_face] = get_face_normals(polytope, new_faces);

                float old_min_distance = FLT_MAX;
                for (size_t i = 0; i < normals.size(); i++) {
                    if (normals[i].w < old_min_distance) {
                        old_min_distance = normals[i].w;
                        min_face = i;
                    }
                }

                if (new_normals[new_min_face].w < old_min_distance) {
                    min_face = new_min_face + normals.size();
                }

                faces.insert(faces.end(), new_faces.begin(), new_faces.end());
                normals.insert(normals.end(), new_normals.begin(), new_normals.end());
            }
        }

        CollisionPoints points{};
        points.normal = min_normal;
        points.depth = min_distance + 0.001f;
        points.has_collision = true;

        return points;
    }

    std::pair<std::vector<glm::vec4>, size_t> get_face_normals(const std::vector<glm::vec3> &polytope, const std::vector<size_t> &faces) {
        std::vector<glm::vec4> normals;
        size_t min_triangle = 0;
        float min_distance = FLT_MAX;

        for (size_t i = 0; i < faces.size(); i += 3) {
            auto a = polytope[faces[i]];
            auto b = polytope[faces[i + 1]];
            auto c = polytope[faces[i + 2]];

            auto normal = glm::normalize(glm::cross((b - a), (c - a)));
            float distance = glm::dot(normal, a);

            if (distance < 0 ) {
                normal *= -1;
                distance *= -1;
            }

            normals.emplace_back(normal, distance);

            if (distance < min_distance) {
                min_triangle = i / 3;
                min_distance = distance;
            }
        }

        return { normals, min_triangle };
    }

    void add_if_unique_edge(std::vector<std::pair<size_t, size_t>> &edges, const std::vector<size_t> &faces, size_t a, size_t b) {
        auto reverse = std::find(edges.begin(), edges.end(), std::make_pair(faces[b], faces[a]));

        if (reverse != edges.end()) {
            edges.erase(reverse);
        } else {
            edges.emplace_back(faces[a], faces[b]);
        }
    }

    inline bool next_simplex(Simplex &points, glm::vec3 &direction) {
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
        auto ao =   - a;

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
                    points = { a, c, b };
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