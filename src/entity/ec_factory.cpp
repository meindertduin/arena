#include "ec_factory.h"
#include "../global.h"
#include "ec_transform.h"
#include "ec_first_person_camera.h"
#include "ec_control.h"
#include "ec_rigid_body.h"
#include "../game/game_state.h"

namespace entity {
    Entity ECFactory::create_player() {
        auto e = global.ecs->create_entity();
        auto transform = ECTransform();
        e.add(transform);
        e.add(ECFirstPersonCamera());
        e.add(ECControl());

        auto collision = ECRigidBody(true, e.get_ptr<ECTransform>());
        auto cube = global.game->cache().get_resource<graphics::Mesh>("assets/fan_tree.obj");
        collision.set_collider(std::make_shared<physics::MeshCollider>(cube));

        e.add(collision);

        auto &camera_component = e.get<ECFirstPersonCamera>();
        camera_component.position_camera();

        return e;
    }

    Entity ECFactory::create_tree() {
        auto e = global.ecs->create_entity();
        e.add(entity::ECTransform({ 0, -24, -10 }, {}));
        auto collision = entity::ECCollisionObject(false, e.get_ptr<ECTransform>());

        auto tree_mesh = global.game->cache().get_resource<graphics::Mesh>("assets/fan_tree.obj");
        auto texture = global.game->cache().get_resource<graphics::Texture>("assets/fan_tree.png");

        auto material = std::make_shared<graphics::Material>(glm::vec3{ 0.2f, 0.2f, 0.2f }, glm::vec3{ 0.6f, 0.6f, 0.6f }, glm::vec3{ 0.2f, 0.2f, 0 }, 0.2f);
        material->add_texture(texture);
        material->set_shader(global.game->cache().get_resource<graphics::ShaderProgram>("shaders/light_shader"));
        auto mesh_renderer = entity::EcStaticMeshRenderer(tree_mesh, material);

        collision.set_collider(std::make_shared<physics::MeshCollider>(tree_mesh));

        e.add(mesh_renderer);
        e.add(collision);

        return e;
    }
}