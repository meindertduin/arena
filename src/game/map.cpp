#include "map.h"

#include "../global.h"
#include "../graphics/renderer.h"
#include "scene.h"

namespace game {
    Map::Map() {
        auto cache = global.application->engine()->cache();
        terrain = cache->get_resource<graphics::Terrain>("assets/terrain.ter");
    }

    void Map::render_background() const {
        auto &render_world = global.application->engine()->active_scene()->render_world();
        global.renderer->render(*render_world, terrain->mesh().get(), terrain->transform());
    }
}