#pragma once

#include "point.h"
#include "quaternion.h"
#include <glm/glm.hpp>

namespace math {
    class AABB {
    public:
        AABB() = default;
        AABB(const glm::vec3 &min, const glm::vec3 &max) :
            m_min{min},
            m_max{max}
            {}

        explicit AABB(float max) :
            m_min(-max),
            m_max(max)
        {}

        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& min() const { return m_min; }
        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& max() const { return m_max; }
        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& center() const { return m_center; }

        void set_center(const glm::vec3& center) { m_center = center; }

        [[nodiscard]] bool inside(const AABB &other) const {
            auto other_min = other.min() + other.center();
            auto other_max = other.max() + other.center();

            auto min = m_min + m_center;
            auto max = m_max + m_center;

            return(max.x > other_min.x &&
                   min.x < other_max.x &&
                   max.y > other_min.y &&
                   min.y < other_max.y &&
                   max.z > other_min.z &&
                   min.z < other_max.z);
        }
    private:
        glm::vec3 m_min{};
        glm::vec3 m_max{};
        glm::vec3 m_center{};
    };
}