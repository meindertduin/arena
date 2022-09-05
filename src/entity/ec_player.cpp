#include "ec_player.h"

#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_collision_box.h"

namespace entity {
    Entity ECPlayer::create(Entity e) const {
        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECCollisionBox(-1, 1, -1, 1, -1, 1, transform));

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }
}
