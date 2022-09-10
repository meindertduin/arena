#pragma once

#include "entity.h"

namespace entity {
    struct ECPlayer {
        [[nodiscard]] Entity create(Entity e) const;
    };
}
