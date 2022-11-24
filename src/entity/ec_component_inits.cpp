#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_static_model.h"
#include "ec_control.h"
#include "ec_rigid_body.h"

namespace entity {
    DECL_COMPONENT_INIT(ECTransform) {}
    DECL_COMPONENT_INIT(ECControl) {}

    DECL_COMPONENT_INIT(ECCollisionObject) {}
    DECL_COMPONENT_INIT(ECRigidBody) {}

    DECL_COMPONENT_INIT(ECFirstPersonCamera) {
        ECFirstPersonCamera::_p->add_event_handler(&ECFirstPersonCamera::on_position_change);
        ECFirstPersonCamera::_p->add_event_handler(&ECFirstPersonCamera::on_rotation_change);
    }

    DECL_COMPONENT_INIT(ECStaticModel) {}
}