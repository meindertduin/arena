#pragma once

#include "entity.h"

namespace entity {
    struct ECPlayer {
        [[nodiscard]] static Entity create(Entity e) ;
    };
}
