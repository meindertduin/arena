#pragma once

#include "ec_transform.h"
#include "../graphics/events.h"

namespace entity {
    class Camera {
    public:
        glm::mat4 view{};
        glm::mat4 projection{};

        ECTransform transform {  };

        Camera(uint32_t screen_width, uint32_t screen_height) {
            transform.pos.z += 10;
            set_projection(screen_width, screen_height);
            view = glm::lookAt(transform.pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

            resize_event_handler = core::create_unique_event_handler<graphics::ScreenResizeEvent>([&](const auto &event) {
                set_projection(event.new_size.width(), event.new_size.height());
            });
        }

        [[nodiscard]] glm::mat4 get_view_4x4() const {
            return glm::mat4_cast(transform.rotation().rotation()) * glm::translate(glm::identity<glm::mat4>(), transform.pos * -1.0f);
        }
    private:
        std::unique_ptr<graphics::ScreenResizeEventHandler> resize_event_handler;

        void set_projection(uint32_t width, uint32_t height) {
            auto aspect_ratio = (float) width / (float) height;
            projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 1000.0f);
        }
    };
}
