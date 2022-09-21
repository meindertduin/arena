#pragma once

#include <string>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"

namespace assets {
    std::shared_ptr<graphics::Mesh> load_obj(const std::string &filename);
    std::shared_ptr<graphics::Terrain> load_terrain(const std::string &filename);

    inline std::shared_ptr<graphics::GpuTexture> load_texture(const std::string &filename) {
        return std::make_shared<graphics::GpuTexture>(filename);
    }
}
