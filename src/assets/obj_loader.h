#pragma once

#include <string>

#include "../graphics/mesh.h"
#include <memory>

namespace assets {
    std::unique_ptr<graphics::MeshData> load_obj(std::string filename);
}
