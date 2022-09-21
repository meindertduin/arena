#include "ec_transform.h"
#include "../global.h"

namespace entity {
    void ECTransform::rotate(float degrees, const glm::vec3 &v) {
        rotation = glm::rotate(rotation, glm::radians(degrees), v);

        RotationChangeEvent event { &this->entity, rotation };
        global.ecs->dispatch_event(&event);
    }


    void ECTransform::move(const glm::vec3 &dir, float amount) {
        pos = pos + (dir * amount);
        
        PositionChangeEvent event { &this->entity };
        global.ecs->dispatch_event(&event);
    }
}
