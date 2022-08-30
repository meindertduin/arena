#include "ec_first_person_camera.h"

#include "../global.h"

namespace entity {
    DECL_COMPONENT_INIT(ECFirstPersonCamera) {
        ECFirstPersonCamera::_p->
            add_event_handler<PositionChangeEvent>(&ECFirstPersonCamera::on_position_change);

        ECFirstPersonCamera::_p->
            add_event_handler<RotationChangeEvent>(&ECFirstPersonCamera::on_rotation_change);
    }

    void ECFirstPersonCamera::on_position_change(PositionChangeEvent event) {

    }

    void ECFirstPersonCamera::on_rotation_change(RotationChangeEvent event) {

    }

    __ECFirstPersonCamera_init camera_init;
}
