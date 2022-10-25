#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace math {
    // TODO, create my own implementation instead of a wrapper
    class Quaternion {
    public:
        Quaternion() = default;

        explicit Quaternion(const glm::quat &rotation) :
            m_rotation{rotation}
            {}

        void rotate(float degrees, const glm::vec3 &v) {
            m_rotation = glm::rotate(m_rotation, glm::radians(degrees), v);
        }

        [[nodiscard]] constexpr glm::vec3 get_forward() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 0.0, -1.0);
        }

        [[nodiscard]] constexpr glm::vec3 get_backward() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 0.0, 1.0);
        }

        [[nodiscard]] constexpr glm::vec3 get_left() const {
            return glm::inverse(m_rotation) * glm::vec3(-1.0, 0.0, 0.0);
        }

        [[nodiscard]] constexpr glm::vec3 get_right() const {
            return glm::inverse(m_rotation) * glm::vec3(1.0, 0.0, 0.0);
        }

        [[nodiscard]] constexpr glm::vec3 get_up() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, 1.0, 0.0);
        }

        [[nodiscard]] constexpr glm::vec3 get_down() const {
            return glm::inverse(m_rotation) * glm::vec3(0.0, -1.0, 0.0);
        }
    private:
        glm::quat m_rotation;
    };
}