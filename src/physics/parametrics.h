#pragma once

#include <glm/glm.hpp>

namespace physics {
static constexpr int PAR_LINE_NO_INTERSECT = 0;
static constexpr int PAR_LINE_INTERSECT_IN_SEGMENT = 1;
static constexpr int PAR_LINE_INTERSECT_OUT_SEGMENT = 2;
static constexpr int PAR_LINE_INTERSECT_EVERYWHERE = 3;


struct Parametric3D {
    glm::vec3 p0; // start point
    glm::vec3 p1; // end point
    glm::vec3 v; // direction of vector

    Parametric3D() = default;
    constexpr Parametric3D(const glm::vec3 &p_init, const glm::vec3 &p_term)
        : p0(p_init), p1(p_term), v(p_term.x - p_init.x, p_term.y - p_init.y, p_term.z - p_init.z) {}

    glm::vec3 compute_point(float t) const {
        return p0 + v * t;
    }
};


struct Plane3D {
    glm::vec3 p0; // point of plane
    glm::vec3 n; // normal of the plane

    Plane3D() = default;
    Plane3D(const glm::vec3 &p0, glm::vec3 &normal, int normalise)
        : p0(p0), n(normalise ? glm::normalize(normal) : normal) {}

    float point_in_plane(const glm::vec3 &p) const;
    Parametric3D parm_line(const glm::vec3 &p, float t) const;

    /*
     * Returns 0 if point lies within plane
     * Returns < 0 if point lies in negative half space
     * Returns > 0 if point lies in positive half space
     * */
    constexpr float compute_point(const glm::vec3 &point) const {
        return n.x * (point.x - p0.x) + n.y * (point.y - p0.y) + n.z * (point.z - p0.z);
    }

    /*
     * Returns 0 if no intersection takes place.
     * Returns 1 when intersection takes place within segment [0, 1]
     * Returns 2 when intersection takes place outside segment [0, 1]
     * Returns 2 when intersection takes everywhere (most likely due to line and plain being parallel)
     * */
    int get_intersect(Parametric3D &line, float &t, glm::vec3 &p_intersect) const;

};

}
