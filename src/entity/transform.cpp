#include "transform.h"

namespace entity {
    DECL_COMPONENT_INIT(Transform) {
        Transform::_p->add_event_handler<TickEvent>(&Transform::on_tick);
    };

    __Transform_init init;
}
