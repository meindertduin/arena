#include "ec_player.h"

#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_collision_box.h"
#include "ec_physics.h"
#include "ec_control.h"
#include "ec_collision.h"
#include "../global.h"
#include "../game/game_state.h"
#include "../physics/collision.h"

namespace entity {
    Entity ECPlayer::create(Entity e) {
        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECPhysics());
        e.add(ECCollisionBox(-1, 1, -1, 1, -1, 1));
        e.add(ECControl());

        auto collision = ECCollision(true);
        auto cube = global.game->cache().get_resource<graphics::Mesh>("assets/fan_tree.obj");
        collision.set_collider(std::make_shared<physics::MeshCollider>(cube));

        e.add(collision);

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }
}
