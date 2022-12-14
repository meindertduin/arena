#pragma once

#include "point.h"
#include "quaternion.h"
#include <glm/glm.hpp>
#include <algorithm>

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

        static AABB create_min() {
            return { glm::vec3{FLT_MAX}, glm::vec3{FLT_MIN} };
        }

        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& min() const { return m_min; }
        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& max() const { return m_max; }
        [[nodiscard]] constexpr ALWAYS_INLINE const glm::vec3& center() const { return m_center; }

        [[nodiscard]] AABB transformed(const glm::vec3 &pos) const {
            return { m_min + pos, m_max + pos };
        }

        void set_center(const glm::vec3& center) { m_center = center; }

        [[nodiscard]] float smallest_side() const {
            auto comp = [](float a, float b) { return a < b; };
            return std::min({ m_max.x - m_min.x, m_max.y - m_min.y, m_max.z - m_min.z}, comp);
        }

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