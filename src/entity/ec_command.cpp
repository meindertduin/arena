#include "ec_command.h"
#include "ec_transform.h"
#include "ec_control.h"

namespace entity {
    void StartMoveCommand::execute(Entity entity) {
        auto &ec_control = entity.get<ECControl>();
        switch (direction) {
            case Direction::Forward:
                ec_control.moves_forward = true;
                break;
            case Direction::Backward:
                ec_control.moves_backward = true;
                break;
            case Direction::Left:
                ec_control.moves_left = true;
                break;
            case Direction::Right:
                ec_control.moves_right = true;
                break;
        }
    }

    void StopMoveCommand::execute(Entity entity) {
        auto &ec_control = entity.get<ECControl>();
        switch (direction) {
            case Direction::Forward:
                ec_control.moves_forward = false;
                break;
            case Direction::Backward:
                ec_control.moves_backward = false;
                break;
            case Direction::Left:
                ec_control.moves_left = false;
                break;
            case Direction::Right:
                ec_control.moves_right = false;
                break;
        }
    }

    void RotateCommand::execute(Entity entity) {
        auto &transform = entity.get<ECTransform>();

        transform.rotate(degrees_x, glm::vec3(0, 1, 0));
        transform.rotate(-degrees_y, transform.rotation().get_right());
    }

}
