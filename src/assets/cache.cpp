#include "cache.h"

#include "loaders.h"
#include "../global.h"

namespace assets {
    template<>
    std::shared_ptr<graphics::Model> Cache::load_asset<graphics::Model>(const Path& path) {
        // Todo add multiple meshes per model
        auto model = std::make_shared<graphics::Model>(path);
        auto mesh_data = load_obj(path);
        graphics::ModelData model_data;
        model_data.meshes.push_back(mesh_data.get());

        model->load(sizeof(model_data), reinterpret_cast<char*>(&model_data));

        m_models[path.hash()] = std::weak_ptr(model);
        return model;
    }

    template<>
    std::shared_ptr<graphics::Terrain> Cache::load_asset<graphics::Terrain>(const Path& path) {
        auto terrain_file = load_terrain(path);
        auto terrain = std::make_shared<graphics::Terrain>(path);
        terrain->load(sizeof(terrain_file), reinterpret_cast<char*>(&terrain_file));
        m_terrains[path.hash()] = std::weak_ptr(terrain);
        return terrain;
    }

    template<>
    std::shared_ptr<graphics::Texture> Cache::load_asset<graphics::Texture>(const Path& path) {
        auto texture = load_texture(path);
        texture->load(0, nullptr);
        m_textures[path.hash()] = std::weak_ptr(texture);
        return texture;
    }

    template<>
    std::shared_ptr<graphics::Shader> Cache::load_asset<graphics::Shader>(const Path& path) {
        auto shader = std::make_shared<graphics::Shader>(path);
        shader->load(0, nullptr);

        m_shaders[path.hash()] = std::weak_ptr(shader);
        return shader;
    }

    template<>
    std::shared_ptr<lua::LuaScript> Cache::load_asset<lua::LuaScript>(const Path& path) {
        auto script = std::make_shared<lua::LuaScript>(path);
        script->load(0, nullptr);

        m_lua_scripts[path.hash()] = std::weak_ptr(script);
        return script;
    }

    template<>
    std::shared_ptr<graphics::Model> Cache::get_resource(const Path& path) {
        auto &model = m_models[path.hash()];
        return get_shared_asset<graphics::Model>(model, path);
    }

    template<>
    std::shared_ptr<graphics::Terrain> Cache::get_resource(const Path& path) {
        auto &terrain = m_terrains[path.hash()];
        return get_shared_asset<graphics::Terrain>(terrain, path);
    }

    template<>
    std::shared_ptr<graphics::Texture> Cache::get_resource(const Path& path) {
        auto &texture = m_textures[path.hash()];
        return get_shared_asset<graphics::Texture>(texture, path);
    }

    template<>
    std::shared_ptr<graphics::Shader> Cache::get_resource(const Path& path) {
        auto &shader = m_shaders[path.hash()];
        return get_shared_asset<graphics::Shader>(shader, path);
    }

    template<>
    std::shared_ptr<lua::LuaScript> Cache::get_resource(const Path& path) {
        auto &script = m_lua_scripts[path.hash()];
        return get_shared_asset<lua::LuaScript>(script, path);
    }
}
