#include "map.h"

#include "../global.h"

namespace game {
    void Terrain::render() {
        global.renderer->render(static_mesh.mesh.get(), this->transform);
    }

    void Map::render_background() {
        terrain->render();
    }
}
