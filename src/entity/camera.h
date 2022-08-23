#pragma once

#include "transform.h"
#include "../global.h"

#include "../graphics/events.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace entity {
    struct Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;

        Transform transform;

        Camera(uint32_t screen_width, uint32_t screen_height) {
            transform.pos = { 0 , 5, 0 };

            set_projection(screen_width, screen_height);
            view = glm::lookAt(transform.pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

            resize_event_handler = core::create_unique_event_handler<graphics::ScreenResizeEvent>([&](const auto &event) {
                set_projection(event.new_screen_dimensions.x, event.new_screen_dimensions.y);
            });
        }

        glm::mat4 get_view_4x4() const {
            return glm::mat4_cast(transform.rotation) * glm::translate(glm::identity<glm::mat4>(), transform.pos * -1.0f);
        }
    private:
        std::unique_ptr<graphics::ScreenResizeEventHandler> resize_event_handler;

        void set_projection(uint32_t width, uint32_t height) {
            auto aspect_ratio = (float) width / (float) height;
            projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 1000.0f);
        }
    };
}
