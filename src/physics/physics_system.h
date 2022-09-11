#pragma once

#include "../entity/system.h"

namespace physics {
    struct PhysicsSystem : public entity::System {
        void update() override;
    };
}
