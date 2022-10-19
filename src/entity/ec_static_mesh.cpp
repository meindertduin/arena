#include "ec_static_mesh.h"

#include "../global.h"
#include "../game/game_state.h"

namespace entity {
    void EcStaticMeshRenderer::init(const std::string& filename) {
        this->mesh = global.game->cache().get_resource<graphics::Mesh>(filename);
        this->material = global.material;
        this->texture = global.texture;
    }
}
