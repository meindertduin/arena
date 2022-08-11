#pragma once

#include "system.h"

namespace entity {
    struct MoveSystem : public System {
        void update() override;
    };
}
