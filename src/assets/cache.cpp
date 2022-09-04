#include "cache.h"

#include "obj_loader.h"

namespace assets {

    template<>
    void Cache::load_asset<graphics::Mesh>(std::string filename) {
        printf("loading asset\n");
        load_obj(filename, this);
    }

    void Cache::save_mesh(std::string filename, std::unique_ptr<graphics::Mesh> mesh) {
        printf("saving mesh\n");
        meshses.insert(std::make_pair(filename, std::move(mesh)));
    }

    graphics::Mesh* Cache::get_mesh(std::string filename) const {
        printf("getting mesh\n");
        auto pair = meshses.find(filename);
        if (pair != meshses.end())
            return pair->second.get();

        return nullptr;
    }
}
