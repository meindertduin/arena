#pragma once

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"
#include "../entity/ec_transform.h"
#include "../entity/ec_static_model.h"

namespace game {
    class Map {
    public:
        Map();

        void render_background() const;
        std::shared_ptr<graphics::Terrain> terrain;
    };
}
