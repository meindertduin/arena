#include "cache.h"

#include "loaders.h"
#include "../global.h"

namespace assets {
    template<>
    std::shared_ptr<graphics::Mesh> Cache::load_asset<graphics::Mesh>(const std::string& filename) {
        return load_obj(filename, this);
    }

    template<>
    std::shared_ptr<graphics::Terrain> Cache::load_asset<graphics::Terrain>(const std::string& filename) {
        return load_terrain(filename, this);
    }

    template<>
    std::shared_ptr<graphics::Mesh> Cache::get_resource(const std::string &filename) {
        auto &mesh = meshes[filename];
        return get_shared_asset<graphics::Mesh>(mesh, filename);
    }

    template<>
    std::shared_ptr<graphics::Terrain> Cache::get_resource(const std::string &filename) {
        auto &terrain = terrains[filename];
        return get_shared_asset<graphics::Terrain>(terrain, filename);
    }
}
