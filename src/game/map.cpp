#include "map.h"

#include "../global.h"

namespace game {
    void Map::render_background() const {
        global.terrain_renderer->render(*terrain);
    }
}
