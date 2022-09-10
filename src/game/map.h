#pragma once

#include "../assets/cache.h"
#include "../graphics/mesh.h"
#include "../graphics/terrain.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_static_mesh.h"

#include "../assets/cache.h"

namespace game {
    struct Map {
    public:
        // TODO load map data from file
        Map() {
            terrain = { "assets/terrain.ter" };
        }

        void render_background() const;
        assets::AssetHandle<graphics::Terrain> terrain;
    };
}
