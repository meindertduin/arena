#include "transform.h"
#include "../global.h"

namespace entity {
    DECL_COMPONENT_INIT(ECTransform) {};

    void ECTransform::rotate(float degrees, const glm::vec3 &v) {
        rotation = glm::rotate(rotation, glm::radians(degrees), v);

        RotationChangeEvent event { rotation };
        event.entity = &this->entity;
        global.ecs->dispatch_event(&event, this->entity);
    }


    void ECTransform::move(const glm::vec3 &dir, float amount) {
        pos = pos + (dir * amount);
        
        // TODO make sending events a little bit more elegant
        PositionChangeEvent event;
        event.entity = &this->entity;
        global.ecs->dispatch_event(&event, this->entity);
    }
}
