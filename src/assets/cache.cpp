#include "cache.h"

#include "loaders.h"
#include "../global.h"
#include "../game/game_state.h"

namespace assets {
    template<>
    void Cache::load_asset<graphics::Mesh>(const std::string& filename) {
        if (meshses.find(filename) == meshses.end())
            load_obj(filename, this);
    }

    template<>
    void Cache::load_asset<graphics::Terrain>(const std::string& filename) {
        if (terrains.find(filename) == terrains.end())
            load_terrain(filename, this);
    }

    graphics::Mesh* Cache::get_mesh(std::string filename) const {
        auto pair = meshses.find(filename);
        if (pair != meshses.end())
            return pair->second.get();

        return nullptr;
    }

    void Cache::save_mesh(std::string filename, std::unique_ptr<graphics::Mesh> mesh) {
        meshses.insert(std::make_pair(filename, std::move(mesh)));
    }

    graphics::Terrain *Cache::get_terrain(std::string filename) const {
        auto pair = terrains.find(filename);
        if (pair != terrains.end())
            return pair->second.get();

        return nullptr;
    }

    void Cache::save_terrain(std::string filename, std::unique_ptr<graphics::Terrain> terrain) {
        terrains.insert(std::make_pair(filename, std::move(terrain)));
    }

    template<>
    graphics::Mesh* AssetHandle<graphics::Mesh>::get() const {
       return global.game->cache.get_mesh(filename);
    }

    template<>
    graphics::Terrain* AssetHandle<graphics::Terrain>::get() const {
        return global.game->cache.get_terrain(filename);
    }
}
