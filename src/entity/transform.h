#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "component.h"
#include "event_manager.h"

namespace entity {
    struct Transform : public ComponentBase {
        glm::vec3 pos;
        glm::quat rotation;

        float scale = 1.0f;

        constexpr Transform(): pos(0.0f, 0.0f, 0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f) {}

        constexpr Transform(const glm::vec3 &pos, const glm::quat &rotation)
            : pos(pos), rotation(rotation) {  }
        constexpr Transform(glm::vec3 &&pos, glm::quat &&rotation)
            : pos(pos), rotation(rotation) {  }

        glm::mat4 get_transform_4x4() const {
            return glm::translate(glm::identity<glm::mat4>(), pos) * glm::mat4_cast(rotation);
        }

        void rotate(float degrees, const glm::vec3 &v) {
            rotation = glm::rotate(rotation, glm::radians(degrees), v);
        }

        void move(const glm::vec3 &dir, float amount) {
            pos = pos + (dir * amount);
        }

        glm::vec3 get_forward() {
            return glm::inverse(rotation) * glm::vec3(0.0, 0.0, -1.0);
        }

        glm::vec3 get_backward() {
            return glm::inverse(rotation) * glm::vec3(0.0, 0.0, 1.0);
        }

        glm::vec3 get_left() {
            return glm::inverse(rotation) * glm::vec3(-1.0, 0.0, 0.0);
        }

        glm::vec3 get_right() {
            return glm::inverse(rotation) * glm::vec3(1.0, 0.0, 0.0);
        }

        glm::vec3 get_up() {
            return glm::inverse(rotation) * glm::vec3(0.0, 1.0, 0.0);
        }

        glm::vec3 get_down() {
            return glm::inverse(rotation) * glm::vec3(0.0, -1.0, 0.0);
        }

        void on_tick(TickEvent event) {
            rotate(1, { 0, 1, 0 });
        }
    };
}
