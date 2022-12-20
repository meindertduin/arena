#include "ec_transform.h"
#include "../global.h"
#include "../game/scene.h"

namespace entity {
    void ECTransform::rotate(float degrees, const glm::vec3 &v) {
        m_rotation.rotate(degrees, v);

        RotationChangeEvent event { &this->entity, m_rotation.rotation() };
        scene->ecs()->dispatch_event(&event);
    }


    void ECTransform::move(const glm::vec3 &dir, float amount) {
        pos = pos + (dir * amount);
        
        PositionChangeEvent event { &this->entity };
        scene->ecs()->dispatch_event(&event);
    }

    void ECTransform::move(const glm::vec3 &dir) {
        pos = pos + dir;

        PositionChangeEvent event { &this->entity };
        scene->ecs()->dispatch_event(&event);
    }
}
