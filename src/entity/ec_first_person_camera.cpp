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
        auto &entity_transform = this->entity.get<Transform>();
        global.game->camera->transform.pos = entity_transform.pos;
    }

    void ECFirstPersonCamera::on_rotation_change(RotationChangeEvent event) {
        global.game->camera->transform.rotation = event.rotation;
    }

    __ECFirstPersonCamera_init camera_init;
}
