#pragma once

#include <glm/glm.hpp>
#include "../platform/platform.h"

namespace graphics {
    class Color {
    public:
        Color() = default;
        constexpr Color(const glm::vec4 &color) : m_color{color} { }
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
            : m_color{(float) r / 255.f, (float) g / 255.f, (float) b / 255.f, (float) a / 255.f } { }

        [[nodiscard]] constexpr ALWAYS_INLINE glm::vec4 color() const { return m_color; }

        [[nodiscard]] constexpr ALWAYS_INLINE float red() const { return m_color.r; }
        [[nodiscard]] constexpr ALWAYS_INLINE float green() const { return m_color.g; }
        [[nodiscard]] constexpr ALWAYS_INLINE float blue() const { return m_color.b; }
        [[nodiscard]] constexpr ALWAYS_INLINE float alpha() const { return m_color.a; }
    private:
        glm::vec4 m_color;
    };
}