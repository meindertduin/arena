#include "map.h"

#include "../global.h"
#include "../graphics/renderer.h"

namespace game {
    Map::Map() {
        auto cache = global.application->engine()->cache();
        terrain = cache->get_resource<graphics::Terrain>("assets/terrain.ter");
    }

    void Map::render_background() const {
        global.renderer->render(terrain->mesh().get(), terrain->transform());
    }
}