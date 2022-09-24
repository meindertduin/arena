#pragma once

#include "system.h"

namespace entity {
    class MovementSystem : public System {
    public:
        void update() override;
    };
}