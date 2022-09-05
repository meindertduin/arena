#pragma once

#include <glm/glm.hpp>

#include "component.h"
#include "event_manager.h"

namespace entity {
    struct ECFirstPersonCamera : Component<ECFirstPersonCamera> {
        void position_camera();
        void on_position_change(PositionChangeEvent event);
        void on_rotation_change(RotationChangeEvent event);
    };

    DECL_COMPONENT_HEADER(ECFirstPersonCamera);
}
