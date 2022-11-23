#pragma once

#include <string>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"
#include "../core/path.h"

namespace assets {
    std::unique_ptr<graphics::MeshData> load_obj(const Path &path);
    std::shared_ptr<graphics::Terrain> load_terrain(const Path &path);
    graphics::ShaderProgram::ShaderProgramData load_shader(const Path &path);

    inline std::shared_ptr<graphics::Texture> load_texture(const Path &path) {
        return std::make_shared<graphics::Texture>(path.path());
    }
}
