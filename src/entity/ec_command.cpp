#include "ec_command.h"
#include "transform.h"

namespace entity {
    void MoveCommand::execute(Entity entity) {
        auto transform = entity.get<Transform>();

        // remove magic number and retrieve from speed component
        transform.move(direction, 0.2f);
    }

    void RotateCommand::execute(Entity entity) {
        auto transform = entity.get<Transform>();

        transform.rotate(degrees_x, glm::vec3(0, 1, 0));
        transform.rotate(-degrees_y, glm::vec3(0, 1, 0));
    }
}
