#include "ec_player.h"

#include "transform.h"
#include "ec_first_person_camera.h"

namespace entity {
    Entity ECPlayer::create(Entity e) const {
        e.add(Transform());
        e.add(ECFirstPersonCamera());
        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }
}
