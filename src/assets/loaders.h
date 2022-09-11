#pragma once

#include <string>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"

namespace assets {
    struct Cache;
    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename, Cache *cache);
    std::shared_ptr<graphics::Terrain> load_terrain(const std::string &filename, Cache *cache);
}
