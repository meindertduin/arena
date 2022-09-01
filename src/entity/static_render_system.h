#pragma once

#include "system.h"

namespace entity {
    struct StaticRenderSystem : public System {
        void update() override;
    };
}
