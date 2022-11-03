#pragma once

#include "simplex.h"
#include "collision.h"

namespace physics {
    std::pair<bool, Simplex> gjk(const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b);

    CollisionPoints epa(const Simplex &simplex,const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b);

    inline glm::vec3 support(const Collider *c_a, const Collider *c_b, const Transform &t_a, const Transform &t_b, const glm::vec3 &direction);

    std::pair<std::vector<glm::vec4>, size_t> get_face_normals(const std::vector<glm::vec3> &polytope, const std::vector<size_t> &faces);

    void add_if_unique_edge(std::vector<std::pair<size_t, size_t>> &edges, const std::vector<size_t> &faces, size_t a, size_t b);

    inline bool next_simplex(Simplex& points, glm::vec3 &direction);

    inline bool same_direction(const glm::vec3 &direction, const glm::vec3 &ao);

    inline bool line(Simplex &points, glm::vec3 &direction);

    inline bool triangle(Simplex &points, glm::vec3 &direction);

    inline bool tetrahedron(Simplex &points, glm::vec3 &direction);
}

