#pragma once

#include "transform.h"
#include "../global.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace entity {
    struct Camera {
        glm::mat4 view;
        glm::mat4 projection;

        Transform transform;

        Camera(uint32_t screen_width, uint32_t screen_height) {
            transform.pos = { 0 , 5, 0 };

            auto aspect_ratio = (float) screen_width / (float) screen_height;

            projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 1000.0f);
            view = glm::lookAt(transform.pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        }

        glm::mat4 get_view_4x4() const {
            return glm::mat4_cast(transform.rotation) * glm::translate(glm::identity<glm::mat4>(), transform.pos * -1.0f);
        }
    };
}
