#pragma once

#include "system.h"

namespace entity {
    struct TerrainCollisionSystem : public System {
        void update() override;
    };
}
