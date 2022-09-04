#pragma once

#include <memory>
#include <unordered_map>

#include "../graphics/mesh.h"
#include "obj_loader.h"

namespace assets {
    struct Cache;
    
    class Cache {
    public:
        Cache() = default;
        ~Cache() = default;

        Cache(const Cache &other) = delete;
        Cache(Cache &&other) = delete;

        Cache& operator=(const Cache &other) = delete;
        Cache& operator=(Cache &&other) = delete;

        template<typename T>
        void load_asset(std::string filename) {
        }

        graphics::Mesh* get_mesh(std::string filename) const;
        void save_mesh(std::string filename, std::unique_ptr<graphics::Mesh> mesh);
    private:
        std::unordered_map<std::string, std::unique_ptr<graphics::Mesh>> meshses;
    };

    template<typename T>
    struct AssetHandle {
    public:
        AssetHandle() = default;
        AssetHandle(std::string filename) : filename(filename) {  }
        T* get() {
            throw std::runtime_error("specialization of type T not implemented.");
        }
    private:
        std::string filename;
    };
}
