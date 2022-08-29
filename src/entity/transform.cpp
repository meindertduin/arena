#include "transform.h"

namespace entity {
    DECL_EVENT_INIT(TickEvent);
    DECL_COMPONENT_INIT(Transform) {
        Transform::_p->add_event_handler<TickEvent>(&Transform::on_tick);
    };

    static __Transform_init init;
}
