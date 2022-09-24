#include "movement_system.h"
#include "ec_transform.h"
#include "ec_control.h"

namespace entity {
    void MovementSystem::update() {
        for (auto &entity : entities) {
            auto &transform = entity.get<ECTransform>();
            const auto &ec_control = entity.get<ECControl>();

            if (ec_control.moves_forward && !ec_control.moves_backward) {
                transform.move(transform.get_forward(), 0.2f);
            } else if (ec_control.moves_backward && !ec_control.moves_forward) {
                transform.move(transform.get_backward(), 0.2f);
            }

            if (ec_control.moves_right && !ec_control.moves_left) {
                transform.move(transform.get_right(), 0.2f);
            } else if (ec_control.moves_left && !ec_control.moves_right) {
                transform.move(transform.get_left(), 0.2f);
            }
        }
    }
}
