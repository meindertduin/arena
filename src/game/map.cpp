#include "map.h"

#include "../global.h"

namespace game {
    void Map::render_background() {
        this->terrain->render();
    }
}
