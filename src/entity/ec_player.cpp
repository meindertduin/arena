#include "ec_player.h"

#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_collision_box.h"
#include "ec_physics.h"

namespace entity {
    Entity ECPlayer::create(Entity e) {
        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECPhysics());
        e.add(ECCollisionBox(-1, 1, -1, 1, -1, 1));

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }
}
