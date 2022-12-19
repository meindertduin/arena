#include "ec_factory.h"
#include "../global.h"
#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_control.h"
#include "ec_rigid_body.h"
#include "../graphics/model.h"
#include "../physics/collision.h"
#include "ec_static_model.h"

namespace entity {
    Entity ECFactory::create_player() {
        auto cache = global.application->engine()->cache();

        auto e = global.ecs->create_entity();
        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECControl());

        auto collision = ECRigidBody(true, e.get_ptr<ECTransform>());
        auto cube = cache->get_resource<graphics::Model>("assets/cube.obj");
        cube->set_state(graphics::MODEL_HIDDEN);

        collision.set_collider(std::make_shared<physics::MeshCollider>(cube));
        auto mesh_renderer = entity::ECStaticModel(cube);

        e.add(mesh_renderer);
        e.add(collision);

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }

    Entity ECFactory::create_tree() {
        auto cache = global.application->engine()->cache();

        auto e = global.ecs->create_entity();
        e.add(entity::ECTransform({ 0, -24, -10 }, {}));
        auto collision = entity::ECCollisionObject(false, e.get_ptr<ECTransform>());

        auto tree_model = cache->get_resource<graphics::Model>("assets/fan_tree.obj");
        auto texture = cache->get_resource<graphics::Texture>("assets/fan_tree.png");

        auto mesh_renderer = entity::ECStaticModel(tree_model);

        collision.set_collider(std::make_shared<physics::MeshCollider>(tree_model));

        e.add(mesh_renderer);
        e.add(collision);

        return e;
    }
}