#include "ec_transform.h"
#include "ec_physics.h"
#include "ec_first_person_camera.h"
#include "ec_static_mesh.h"
#include "ec_control.h"
#include "ec_collision.h"

namespace entity {
    DECL_COMPONENT_INIT(ECTransform) {}
    DECL_COMPONENT_INIT(ECPhysics) {}
    DECL_COMPONENT_INIT(ECControl) {}
    DECL_COMPONENT_INIT(ECCollision) {}

    DECL_COMPONENT_INIT(ECFirstPersonCamera) {
        ECFirstPersonCamera::_p->add_event_handler(&ECFirstPersonCamera::on_position_change);
        ECFirstPersonCamera::_p->add_event_handler(&ECFirstPersonCamera::on_rotation_change);
    }

    DECL_COMPONENT_INIT(EcStaticMeshRenderer) {}
}