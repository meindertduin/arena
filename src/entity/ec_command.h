#pragma once

#include <glm/glm.hpp>
#include "entity.h"

namespace entity {
    struct ECCommand {
        virtual void execute(Entity entity) = 0;
    };

    struct MoveCommand : public ECCommand {
        glm::vec3 direction;

        void execute(Entity entity) override;
    };

    struct RotateCommand : public ECCommand {
        float degrees_x;
        float degrees_y;

        void execute(Entity entity) override;
    };
}
