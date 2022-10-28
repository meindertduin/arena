#pragma once

#include "../platform/platform.h"

#include <type_traits>
#include <utility>
#include <glm/vec3.hpp>

namespace math {

    template<typename T>
    class Point2D {
    public:
        Point2D() = default;

        constexpr Point2D(T x, T y) :
            m_x{x},
            m_y{y}
            {}

        template<typename U>
        constexpr Point2D(U &&x, U &&y) :
            m_x{std::forward<T>(x)},
            m_y{std::forward<T>(y)}
            {}

        constexpr ALWAYS_INLINE  T x() const { return m_x; }
        constexpr ALWAYS_INLINE T y() const { return m_y; }

        ALWAYS_INLINE void set_x(T x) { m_x = x; }
        ALWAYS_INLINE void set_y(T y) { m_y = y; }

        template<typename U>
        bool operator==(const Point2D<U> &other) const {
            return m_x == other.x() && m_y == other.y();
        }

        template<typename U>
        bool operator!=(const Point2D<U> &other) const {
            return !(*this == other);
        }

    private:
        T m_x { 0 };
        T m_y { 0 };
    };

    template<typename T>
    class Point3D {
    public:
        Point3D() = default;

        constexpr Point3D(T x, T y, T z) :
            m_x{x},
            m_y{y},
            m_z{z}
            {}

        template<typename U>
        constexpr Point3D(U &&x, U &&y, U &&z) :
            m_x{std::forward<T>(x)},
            m_y{std::forward<T>(y)},
            m_z{std::forward<T>(z)}
            {}

        constexpr ALWAYS_INLINE T x() const { return m_x; }
        constexpr ALWAYS_INLINE T y() const { return m_y; }
        constexpr ALWAYS_INLINE T z() const { return m_z; }

        ALWAYS_INLINE void set_x(T x) { m_x = x; }
        ALWAYS_INLINE void set_y(T y) { m_y = y; }
        ALWAYS_INLINE void set_z(T z) { m_z = z; }

        template<typename U>
        bool operator==(const Point3D<U> &other) const {
            return m_x == other.x() && m_y == other.y() && m_z == other.z();
        }

        template<typename U>
        bool operator!=(const Point2D<U> &other) const {
            return !(*this == other);
        }

        glm::vec3 operator-(const Point3D<T> &other) const {
            return { m_x - other.x(), m_y - other.y(), m_z - other.z() };
        }

    private:
        T m_x { 0 };
        T m_y { 0 };
        T m_z { 0 };
    };
}