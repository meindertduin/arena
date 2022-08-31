#include "ec_command.h"
#include "transform.h"

namespace entity {
    void MoveCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();

        // remove magic number and retrieve from speed component
        transform.move(direction, 0.2f);
    }

    void MoveForwardCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();
        transform.move(transform.get_forward(), 0.2f);
    }

    void MoveBackwardCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();
        transform.move(transform.get_backward(), 0.2f);
    }

    void MoveLeftCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();
        transform.move(transform.get_left(), 0.2f);
    }

    void MoveRightCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();
        transform.move(transform.get_right(), 0.2f);
    }

    void RotateCommand::execute(Entity entity) {
        auto &transform = entity.get<Transform>();

        transform.rotate(degrees_x, glm::vec3(0, 1, 0));
        transform.rotate(-degrees_y, transform.get_right());
    }
}
