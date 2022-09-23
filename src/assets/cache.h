#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"

#include "../logging.h"
#include "loaders.h"

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
        std::shared_ptr<T> get_resource(const std::string &filename) {
            THROW_ERROR("specialization for function 'get_resource' of type %s not implemented for cache get()", typeid(T).name());
        }
    private:
        std::unordered_map<std::string, std::weak_ptr<graphics::Mesh>> meshes;
        std::unordered_map<std::string, std::weak_ptr<graphics::Terrain>> terrains;
        std::unordered_map<std::string, std::weak_ptr<graphics::Texture>> textures;

        template<typename T>
        std::shared_ptr<T> load_asset(const std::string& filename) {
            THROW_ERROR("specialization for function 'load_asset' of type %s not implemented for cache get()", typeid(T).name());
        }

        template<typename T>
        std::shared_ptr<T> get_shared_asset(std::weak_ptr<T> &resource, const std::string &filename) {
            auto loaded_resource = resource.lock();
            if (loaded_resource) {
                return loaded_resource;
            }

            return load_asset<T>(filename);
        }
    };
}
