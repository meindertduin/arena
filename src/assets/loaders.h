#pragma once

#include <string>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"
#include "../core/path.h"

namespace assets {
    std::unique_ptr<graphics::MeshData> load_obj(const Path &path);
    graphics::TerrainFile load_terrain(const Path &path);
}
