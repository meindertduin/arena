#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../platform/platform.h"

namespace math {
    // TODO, create my own implementation instead of a wrapper
    class Quaternion {
    public:
        constexpr Quaternion() = default;
        constexpr explicit Quaternion(const glm::quat &rotation) :
            m_rotation{rotation}
            {}

        void rotate(float degrees, const glm::vec3 &v) {
            m_rotation = glm::rotate(m_rotation, glm::radians(degrees), v);
        }

        [[nodiscard]] constexpr ALWAYS_INLINE const glm::quat& rotation() const { return m_rotation; }
        [[nodiscard]] constexpr ALWAYS_INLINE glm::quat& rotation() { return m_rotation; }

        constexpr void set_rotation(const glm::quat &rotation) { m_rotation = rotation; }

        [[nodiscard]] glm::vec3 get_forward() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 0.0, -1.0);
        }

        [[nodiscard]] glm::vec3 get_backward() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 0.0, 1.0);
        }

        [[nodiscard]] glm::vec3 get_left() const {
            return glm::inverse(m_rotation) * glm::vec3(-1.0, 0.0, 0.0);
        }

        [[nodiscard]] glm::vec3 get_right() const {
            return glm::inverse(m_rotation) * glm::vec3(1.0, 0.0, 0.0);
        }

        [[nodiscard]] glm::vec3 get_up() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 1.0, 0.0);
        }

        [[nodiscard]] glm::vec3 get_down() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, -1.0, 0.0);
        }
    private:
        glm::quat m_rotation;
    };
}