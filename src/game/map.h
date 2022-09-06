#pragma once

#include "../assets/cache.h"
#include "../graphics/mesh.h"
#include "../graphics/terrain.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_static_mesh.h"

namespace game {
    struct Map {
    public:
        // TODO load map data from file
        Map() {
            terrain = std::make_unique<graphics::Terrain>("assets/heightmap.png");
        }

        void render_background();
    private:
        std::unique_ptr<graphics::Terrain> terrain;
    };
}
