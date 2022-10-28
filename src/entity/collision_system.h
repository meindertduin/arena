#pragma once

#include "system.h"

namespace entity {
    class CollisionSystem : public System {
    public:
        void update() override;
    };
}