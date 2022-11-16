#include "ec_factory.h"
#include "../global.h"
#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_control.h"
#include "ec_rigid_body.h"
#include "../game/game_state.h"
#include "../physics/collision.h"

namespace entity {
    Entity ECFactory::create_player() {
        auto e = global.ecs->create_entity();

        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECControl());

        auto collision = ECRigidBody(true);
        auto cube = global.game->cache().get_resource<graphics::Mesh>("assets/fan_tree.obj");
        collision.set_collider(std::make_shared<physics::MeshCollider>(cube));

        e.add(collision);

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }

    Entity ECFactory::create_tree() {
        auto e = global.ecs->create_entity();
        auto collision = entity::ECRigidBody(false);

        auto tree_mesh = global.game->cache().get_resource<graphics::Mesh>("assets/fan_tree.obj");

        auto mesh_renderer = entity::EcStaticMeshRenderer(tree_mesh);
        collision.set_collider(std::make_shared<physics::MeshCollider>(tree_mesh));

        e.add(mesh_renderer);
        e.add(collision);
        e.add(entity::ECTransform({ 0, -24, -10 }, {}));

        return e;
    }
}