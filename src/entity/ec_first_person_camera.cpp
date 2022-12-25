#include "ec_first_person_camera.h"

#include "../global.h"
#include "../game/scene.h"
#include "ec_transform.h"

namespace entity {

    void ECFirstPersonCamera::position_camera() {
        auto &entity_transform = this->entity.get<ECTransform>();
        scene->render_world()->camera().transform.pos = entity_transform.pos;
    }

    void ECFirstPersonCamera::on_position_change(PositionChangeEvent event) {
        auto &entity_transform = this->entity.get<ECTransform>();
        scene->render_world()->camera().transform.pos = entity_transform.pos;
    }

    void ECFirstPersonCamera::on_rotation_change(RotationChangeEvent event) {
        scene->render_world()->camera().transform.rotation().set_rotation(event.rotation);
    }
}