#pragma once

#include "point.h"
#include "quaternion.h"
#include <glm/glm.hpp>

namespace math {
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

        [[nodiscard]] constexpr ALWAYS_INLINE const Point3D<T>& center() const { return m_center; }
        [[nodiscard]] constexpr ALWAYS_INLINE const Quaternion& rotation() const { return m_rotation; }
        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& half() const { return m_half; }

        void set_rotation(const Quaternion &rotation) { m_rotation = rotation; }
        void set_center(const Point3D<float> &center) { m_center = center; }

        bool inside(const Point3D<T> &point) const {
            auto delta = point - m_center;

            // TODO, optimize. get_right() etc are quite costly.
            return fabs(glm::dot(delta, m_rotation.get_right())) <= m_half.x &&
                   fabs(glm::dot(delta, m_rotation.get_up())) <= m_half.y &&
                   fabs(glm::dot(delta, m_rotation.get_forward())) <= m_half.z;
        }

        [[nodiscard]] bool inside(const Box3D<T> &other) const {
            glm::vec3 RPos = other.center() - center();

            if (getSeparatingPlane(RPos, m_rotation.get_right(), other) || getSeparatingPlane(RPos, m_rotation.get_up(), other) || getSeparatingPlane(RPos, m_rotation.get_forward(), other) ||
                getSeparatingPlane(RPos, other.rotation().get_right(), other) || getSeparatingPlane(RPos, other.rotation().get_up(), other) || getSeparatingPlane(RPos, other.rotation().get_forward(), other) ||
                    getSeparatingPlane(RPos, glm::cross(m_rotation.get_right(), other.rotation().get_right()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_right(), other.rotation().get_up()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_right(), other.rotation().get_forward()), other) ||
                    getSeparatingPlane(RPos, glm::cross(m_rotation.get_up(), other.rotation().get_right()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_up(), other.rotation().get_up()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_up(), other.rotation().get_forward()), other) ||
                    getSeparatingPlane(RPos, glm::cross(m_rotation.get_forward(), other.rotation().get_right()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_forward(), other.rotation().get_up()), other) || getSeparatingPlane(RPos, glm::cross(rotation().get_forward(), other.rotation().get_forward()), other))
            {
                return false;
            }

            return true;
        }

    private:
        Point3D<T> m_center;
        Quaternion m_rotation{ { 1, 0, 0, 0 } };
        glm::vec3 m_half{};

        [[nodiscard]] bool getSeparatingPlane(const glm::vec3& RPos, const glm::vec3 Plane, const Box3D<float> &other) const {
            auto self_sep = fabs(glm::dot((m_rotation.get_right() * m_half.x), Plane)) +
                    fabs(glm::dot((m_rotation.get_up() * m_half.y), Plane)) +
                    fabs(glm::dot((m_rotation.get_forward() * m_half.z), Plane));

            auto other_sep = fabs(glm::dot((other.rotation().get_right() * other.half().x), Plane)) +
                        fabs(glm::dot((other.rotation().get_up() * other.half().y), Plane)) +
                        fabs(glm::dot((other.rotation().get_forward() * other.half().z), Plane));

            return fabs(glm::dot(RPos, Plane)) > self_sep + other_sep;
        }
    };
}