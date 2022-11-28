#include "map.h"

#include "../global.h"
#include "../graphics/renderer.h"
#include "game_state.h"

namespace game {
    Map::Map() {
        terrain = global.game->cache().get_resource<graphics::Terrain>("assets/terrain.ter");
    }

    void Map::render_background() const {
        global.renderer->render(terrain->mesh().get(), terrain->transform());
    }
}