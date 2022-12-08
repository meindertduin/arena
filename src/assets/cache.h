#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "../graphics/mesh.h"
#include "../graphics/terrain.h"

#include "../logging.h"
#include "../graphics/model.h"
#include "../lua/lua_script.h"

namespace assets {
    class Cache;

    class Cache {
    public:
        Cache() = default;
        ~Cache() = default;

        Cache(const Cache &other) = delete;
        Cache(Cache &&other) = delete;

        Cache& operator=(const Cache &other) = delete;
        Cache& operator=(Cache &&other) = delete;

        template<typename T>
        std::shared_ptr<T> get_resource(const Path &path) {
            THROW_ERROR("specialization for function 'get_resource' of m_type %s not implemented for cache get()", typeid(T).name());
            return nullptr;
        }

        template<typename T>
        std::shared_ptr<T> get_resource(const std::string &path) {
            return get_resource<T>(Path {path});
        }

    private:
        std::unordered_map<Hash64, std::weak_ptr<graphics::Model>> m_models;
        std::unordered_map<Hash64, std::weak_ptr<graphics::Terrain>> m_terrains;
        std::unordered_map<Hash64, std::weak_ptr<graphics::Texture>> m_textures;
        std::unordered_map<Hash64, std::weak_ptr<graphics::Shader>> m_shaders;
        std::unordered_map<Hash64, std::weak_ptr<graphics::Material>> m_materials;
        std::unordered_map<Hash64, std::weak_ptr<lua::LuaScript>> m_lua_scripts;

        template<typename T>
        std::shared_ptr<T> load_asset(const Path& path) {
            THROW_ERROR("specialization for function 'load_asset' of m_type %s not implemented for cache get()", typeid(T).name());
            return nullptr;
        }

        template<typename T>
        std::shared_ptr<T> get_shared_asset(std::weak_ptr<T> &resource, const Path &path) {
            auto loaded_resource = resource.lock();
            if (loaded_resource) {
                return loaded_resource;
            }

            return load_asset<T>(path);
        }
    };
}
