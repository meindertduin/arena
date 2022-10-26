#include "ec_collision.h"

#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    void ECCollision::init(const std::string &filename) {
        this->mp_mesh = global.game->cache().get_resource<graphics::Mesh>(filename);
    }
}
