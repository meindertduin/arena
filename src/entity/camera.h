#pragma once

#include "transform.h"
#include "../global.h"

#include "../graphics/events.h"
#include "../input/input.h"
#include "../input/events.h"

#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace entity {
    struct Camera {
    public:
        glm::mat4 view;
        glm::mat4 projection;

        Transform transform;

        std::unique_ptr<core::EventHandler<input::MouseEvent>> mouseEventHandler;
        std::unique_ptr<core::EventHandler<input::KeyEvent>> keyEventHandler;

        Camera(uint32_t screen_width, uint32_t screen_height) {
            set_projection(screen_width, screen_height);
            view = glm::lookAt(transform.pos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

            resize_event_handler = core::create_unique_event_handler<graphics::ScreenResizeEvent>([&](const auto &event) {
                set_projection(event.new_screen_dimensions.x, event.new_screen_dimensions.y);
            });

            mouseEventHandler = core::create_unique_event_handler<input::MouseEvent>(
                   [&](const input::MouseEvent &event) { on_mouse_movement(event.mouse_x_offset, event.mouse_y_offset); });

            keyEventHandler = core::create_unique_event_handler<input::KeyEvent>(
                   [&](const input::KeyEvent &event) { on_key_event(event.key, event.mods, event.action); });

        }

        glm::mat4 get_view_4x4() const {
            return glm::mat4_cast(transform.rotation) * glm::translate(glm::identity<glm::mat4>(), transform.pos * -1.0f);
        }

        void update() {
            if (moves_forward && !moves_backward) {
                transform.move(transform.get_forward(), 0.2f);
            } else if (moves_backward && !moves_forward) {
                transform.move(transform.get_backward(), 0.2f);
            }

            if (moves_right && !moves_left) {
                transform.move(transform.get_right(), 0.2f);
            } else if (moves_left && !moves_right) {
                transform.move(transform.get_left(), 0.2f);
            }
        }

    private:
        bool moves_forward = false;
        bool moves_backward = false;
        bool moves_left = false;
        bool moves_right = false;

        float movement_speed = 2.5f;
        float mouse_sensitivity = 0.1f;

        std::unique_ptr<graphics::ScreenResizeEventHandler> resize_event_handler;

        void set_projection(uint32_t width, uint32_t height) {
            auto aspect_ratio = (float) width / (float) height;
            projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 1000.0f);
        }

        void on_mouse_movement(float mouseXOffset, float mouseYOffset) {
            auto xoffset = mouseXOffset;
            auto yoffset = mouseYOffset;

            xoffset *= mouse_sensitivity;
            yoffset *= mouse_sensitivity;

            transform.rotate(xoffset,  glm::vec3(0, 1, 0));
            transform.rotate(-yoffset, transform.get_right());
        }

        void on_key_event(int key, int mods_mask, int action) {
            if (key == input::KEY_W || key == input::KEY_S || key == input::KEY_A || key == input::KEY_D) {
                if (action == input::KEY_PRESS || action == input::KEY_RELEASE) {
                    auto enable_movement = action == input::KEY_PRESS;
                    switch(key) {
                        case input::KEY_W:
                            moves_forward = enable_movement;
                            break;
                        case input::KEY_S:
                            moves_backward = enable_movement;
                            break;
                        case input::KEY_A:
                            moves_left = enable_movement;
                            break;
                        case input::KEY_D:
                            moves_right = enable_movement;
                            break;
                    }
                }
            }
        }

    };
}
