#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "component.h"
#include "event_manager.h"
#include "../math/quaternion.h"

namespace entity {
    struct ECTransform : public Component<ECTransform> {
        glm::vec3 pos;

        float scale = 1.0f;

        constexpr ECTransform(): Component(),
            pos(0.0f, 0.0f, 0.0f),
            m_rotation({ 1.0f, 0.0f, 0.0f, 0.0f })
            {}

        constexpr ECTransform(const glm::vec3 &pos, const glm::quat &rotation) : Component(),
            pos(pos), m_rotation(rotation)
            {}

        constexpr ECTransform(glm::vec3 &&pos, glm::quat &&rotation) : Component(),
            pos(pos), m_rotation(rotation)
            {}

        [[nodiscard]] glm::mat4 get_transform_4x4() const {
            return glm::translate(glm::identity<glm::mat4>(), pos) * glm::mat4_cast(m_rotation.rotation());
        }

        void rotate(float degrees, const glm::vec3 &v);
        void move(const glm::vec3 &dir, float amount);
        void move(const glm::vec3 &dir);

        [[nodiscard]] constexpr ALWAYS_INLINE const math::Quaternion& rotation() const { return m_rotation; }
        [[nodiscard]] constexpr ALWAYS_INLINE math::Quaternion& rotation() { return m_rotation; }

    private:
        math::Quaternion m_rotation;
    };

    DECL_COMPONENT_HEADER(ECTransform);
}
