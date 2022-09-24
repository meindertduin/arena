#pragma once

#include <glm/glm.hpp>
#include "entity.h"

namespace entity {
    enum class Direction {
        Forward,
        Backward,
        Left,
        Right,
    };

    struct ECCommand {
        virtual void execute(Entity entity) = 0;
    };

    struct StartMoveCommand : public ECCommand {
        Direction direction;
        StartMoveCommand(Direction direction) : direction{direction} { }

        void execute(Entity entity) override;
    };

    struct StopMoveCommand : public ECCommand {
        Direction direction;
        StopMoveCommand(Direction direction) : direction{direction} { }

        void execute(Entity entity) override;
    };

    struct RotateCommand : public ECCommand {
        float degrees_x;
        float degrees_y;

        void execute(Entity entity) override;
    };
}
