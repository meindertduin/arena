#pragma once

#include "transform.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace entity {
    struct Camera {
        glm::mat4 view;
        glm::mat4 projection;

        Transform transform;

        Camera() {
            transform.pos = { 0 , 5, 0 };
            projection = glm::perspective(glm::radians(45.0f), (float) 1280 / (float) 720, 0.1f, 1000.0f);
            view = glm::lookAt(transform.pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        }

        glm::mat4 get_view_4x4() const {
            return glm::mat4_cast(transform.rotation) * glm::translate(glm::identity<glm::mat4>(), transform.pos * -1.0f);
        }
    };
}
