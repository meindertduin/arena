#pragma once

#include "../platform/platform.h"
#include <type_traits>

namespace graphics {
    template<typename T>
    concept Integral = std::is_integral<T>::value;

    template<typename T>
    class Size {
    public:
        Size() = default;

        constexpr Size(T size) : m_width{size}, m_height{size} {}
        constexpr Size(T width, T height) : m_width{width}, m_height{height} {}

        constexpr ALWAYS_INLINE T width() const { return m_width; }
        constexpr ALWAYS_INLINE T height() const { return m_height; }

        ALWAYS_INLINE void set_width(T width) { m_width = width; }
        ALWAYS_INLINE void set_height(T height) { m_height = height; }

        constexpr ALWAYS_INLINE T area() const { return m_width * m_height; }

        template<typename U>
        bool operator==(const Size<U> &other) const {
            return width() == other.width() && height() == other.height();
        }

    private:
        T m_width;
        T m_height;
    };

    template<Integral T>
    class Point {
    public:
        Point() = default;

        constexpr Point(T x, T y) : m_x{x}, m_y{y} {}

        template<Integral U>
        constexpr Point(U &&x, U &&y) : m_x{static_cast<T>(x)}, m_y{static_cast<T>(y)} {}

        constexpr ALWAYS_INLINE  T x() const { return m_x; }
        constexpr ALWAYS_INLINE T y() const { return m_y; }

        ALWAYS_INLINE void set_x(T x) { m_x = x; }
        ALWAYS_INLINE void set_y(T y) { m_y = y; }

        template<typename U>
        bool operator==(const Point<U> &other) const {
            return m_x == other.x() && m_y == other.y();
        }

        template<typename U>
        bool operator!=(const Point<U> &other) const {
            return *this != other;
        }

    private:
        T m_x { 0 };
        T m_y { 0 };
    };

    template<typename T>
    class Rect {
    public:
        Rect() = default;

        Rect(T x, T y, T width, T height) : m_position{x, y}, m_size{width, height} {}

        Rect(const Point<T> &position, const Size<T> &size) : m_position{position}, m_size{size} {}

        [[nodiscard]] constexpr ALWAYS_INLINE Point<T> position() const { return m_position; }

        [[nodiscard]] constexpr ALWAYS_INLINE Size<T> size() const { return m_size; }

        [[nodiscard]] constexpr bool contains(const Rect<T> &other) const {
            return size().width() >= other.size().width()
                   && size().height() >= other.size().height();
        }

    private:
        Point<T> m_position;
        Size<T> m_size;
    };

    using IPoint = Point<int>;
    using ISize = Size<int>;
    using U32Size = Size<unsigned int>;
    using IRect = Rect<int>;

    IRect convert_to_gl_rect(const IRect &rect);
    IPoint convert_to_gl_point(const IPoint &point, const ISize &size);
    IPoint convert_to_gl_point(const IPoint &point, int height);
    IPoint convert_to_gl_point(const IPoint &point);
}