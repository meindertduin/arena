#include "parametrics.h"

namespace physics {

int Plane3D::get_intersect(Parametric3D &line, float &t, glm::vec3 &p_intersect) const {
    float plane_dot = glm::dot(line.v, n);

    if (std::fabs(plane_dot) <= 0.00005f) {
        if (std::fabs(compute_point(line.p0))) {
            return PAR_LINE_INTERSECT_EVERYWHERE;
        } else {
            return PAR_LINE_NO_INTERSECT;
        }
    }

    t = - (n.x * line.p0.x + n.y * line.p0.y + n.z * line.p0.z -
            n.x * p0.x - n.y * p0.y - n.z * p0.z) / plane_dot;

    p_intersect.x = line.p0.x + line.v.x * t;
    p_intersect.y = line.p0.y + line.v.y * t;
    p_intersect.z = line.p0.z + line.v.z * t;

    if (t >= 0.0f && t <= 1.0f) {
        return PAR_LINE_INTERSECT_IN_SEGMENT;
    } else {
        return PAR_LINE_INTERSECT_OUT_SEGMENT;
    }
}

}
