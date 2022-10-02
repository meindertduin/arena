#pragma once

#include "component.h"

namespace entity {
    struct ECControl : public Component<ECControl> {
        bool is_moving;

        bool moves_forward;
        bool moves_backward;
        bool moves_left;
        bool moves_right;

        float base_movement_speed = 0.1f;
    };

    DECL_COMPONENT_HEADER(ECControl);
}