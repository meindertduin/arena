#include "cache.h"

#include "obj_loader.h"
#include "../global.h"

namespace assets {

    template<>
    void Cache::load_asset<graphics::Mesh>(std::string filename) {
        load_obj(filename, this);
    }

    void Cache::save_mesh(std::string filename, std::unique_ptr<graphics::Mesh> mesh) {
        meshses.insert(std::make_pair(filename, std::move(mesh)));
    }

    graphics::Mesh* Cache::get_mesh(std::string filename) const {
        auto pair = meshses.find(filename);
        if (pair != meshses.end())
            return pair->second.get();

        return nullptr;
    }

    template<>
    graphics::Mesh* AssetHandle<graphics::Mesh>::get()  {
       return global.game->cache.get_mesh(filename);
    }
}
