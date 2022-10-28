#pragma once

#include "../platform/platform.h"
#include "../math/point.h"

namespace graphics {
    using math::Point2D;

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

    template<typename T>
    class Rect {
    public:
        Rect() = default;

        Rect(T x, T y, T width, T height) : m_position{x, y}, m_size{width, height} {}

        Rect(const Point2D<T> &position, const Size<T> &size) : m_position{position}, m_size{size} {}

        [[nodiscard]] constexpr ALWAYS_INLINE Point2D<T> position() const { return m_position; }

        [[nodiscard]] constexpr ALWAYS_INLINE Size<T> size() const { return m_size; }

        [[nodiscard]] constexpr bool contains(const Rect<T> &other) const {
            return size().width() >= other.size().width()
                   && size().height() >= other.size().height();
        }

    private:
        Point2D<T> m_position;
        Size<T> m_size;
    };

    using IPoint2D = Point2D<int>;
    using ISize = Size<int>;
    using U32Size = Size<unsigned int>;
    using IRect = Rect<int>;

    IRect convert_to_gl_rect(const IRect &rect);
    IPoint2D convert_to_gl_point(const IPoint2D &point, const ISize &size);
    IPoint2D convert_to_gl_point(const IPoint2D &point, int height);
    IPoint2D convert_to_gl_point(const IPoint2D &point);
}