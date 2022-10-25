#pragma once

#include "point.h"
#include "quaternion.h"
#include <glm/glm.hpp>

namespace math {
    constexpr glm::vec3 Forward = { 0, 0, 1 };
    constexpr glm::vec3 Up = { 0, 1, 0 };
    constexpr glm::vec3 Right = { 1, 0, 0 };

    template<typename T>
    class Box3D {
    public:
        Box3D() = default;
        explicit Box3D(const glm::vec3 &dimensions) :
            m_half{dimensions * 0.5f}
            {}

        Box3D(const Point3D<T> &center, const glm::vec3 &dimensions) :
            m_center{center},
            m_half{dimensions * 0.5f}
            {}

        Box3D(const Point3D<T> &center, const glm::vec3 &dimensions, const Quaternion &rotation) :
            m_center{center},
            m_half{dimensions * 0.5f},
            m_rotation{rotation}
            {}

        bool inside(const Point3D<T> &point) const {
            auto delta = point - m_center;

            // TODO, optimize. get_right() etc are quite costly.
            return abs(glm::dot(delta, m_rotation.get_right())) <= m_half.x &&
                   abs(glm::dot(delta, m_rotation.get_up())) <= m_half.y &&
                   abs(glm::dot(delta, m_rotation.get_forward())) <= m_half.z;
        }
    private:
        Point3D<T> m_center;
        Quaternion m_rotation{};
        glm::vec3 m_half{};
    };
}