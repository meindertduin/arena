#include "ec_collision.h"

#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    void ECCollision::init(const std::string &filename) {
        this->mp_mesh = global.game->cache().get_resource<graphics::Mesh>(filename);
        if (mp_mesh->collisions_data().empty()) {
            this->m_collider = std::make_shared<physics::MeshCollider>(this->mp_mesh->mesh_data());
        } else {
            auto collision_data = mp_mesh->collisions_data()[0];
            this->m_collider = std::make_shared<physics::MeshCollider>(collision_data);
        }
    }
}
