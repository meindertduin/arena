#pragma once

#include "../platform/platform.h"

namespace graphics {
    template<typename T>
    class Size {
    public:
        Size() = default;
        constexpr Size(T size) : m_width{size}, m_height{size} {}
        constexpr Size(T width, T height) : m_width{width}, m_height{height} {}

        constexpr ALWAYS_INLINE T width() const { return m_width; }
        constexpr ALWAYS_INLINE T height() const { return m_height; }
        constexpr ALWAYS_INLINE T area() const { return m_width * m_height; }
    private:
        T m_width;
        T m_height;
    };

    template<typename T>
    class Point {
    public:
        Point() = default;
        Point(T x, T y) : m_x{x}, m_y{y} {}

        constexpr ALWAYS_INLINE T x() const { return m_x; }
        constexpr ALWAYS_INLINE T y() const { return m_y; }

        template<typename U>
        bool operator==(const Point<U> &other) const {
            return m_x == other.x() && m_y == other.y();
        }

        template<typename U>
        bool operator!=(const Point<U> &other) const {
            return *this != other;
        }
    private:
        T m_x;
        T m_y;
    };

    template<typename T>
    class Rect {
    public:
        Rect() = default;
        Rect(T x, T y, T width, T height) : m_position{x, y}, m_size{width, height} { }
        Rect(const Point<T> &position, const Size<T> &size) : m_position{position}, m_size{size} { }

        constexpr ALWAYS_INLINE Point<T> position() const { return m_position; }
        constexpr ALWAYS_INLINE Size<T> size() const { return m_size; }
    private:
        Point<T> m_position;
        Size<T> m_size;
    };
}