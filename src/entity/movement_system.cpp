#include "movement_system.h"
#include "ec_transform.h"
#include "ec_control.h"

namespace entity {
    void MovementSystem::update() {
        for (auto &entity : entities) {
            auto &transform = entity.get<ECTransform>();
            const auto &ec_control = entity.get<ECControl>();

            auto movement = ec_control.base_movement_speed;

            if (ec_control.moves_forward && !ec_control.moves_backward) {
                transform.move(transform.get_forward(), movement);
            } else if (ec_control.moves_backward && !ec_control.moves_forward) {
                transform.move(transform.get_backward(), movement);
            }

            if (ec_control.moves_right && !ec_control.moves_left) {
                transform.move(transform.get_right(), movement);
            } else if (ec_control.moves_left && !ec_control.moves_right) {
                transform.move(transform.get_left(), movement);
            }
        }
    }
}
