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
    std::shared_ptr<graphics::Mesh> Cache::load_asset<graphics::Mesh>(const Path& path) {
        auto mesh = std::make_shared<graphics::Mesh>(path);
        auto mesh_data = load_obj(path);

        mesh->load(sizeof(mesh_data), reinterpret_cast<char*>(mesh_data.get()));

        m_meshes[path.hash()] = std::weak_ptr(mesh);
        return mesh;
    }

    template<>
    std::shared_ptr<graphics::Terrain> Cache::load_asset<graphics::Terrain>(const Path& path) {
        auto terrain = load_terrain(path);
        m_terrains[path.hash()] = std::weak_ptr(terrain);
        return terrain;
    }

    template<>
    std::shared_ptr<graphics::Texture> Cache::load_asset<graphics::Texture>(const Path& path) {
        auto texture = load_texture(path);
        m_textures[path.hash()] = std::weak_ptr(texture);
        return texture;
    }

    template<>
    std::shared_ptr<graphics::ShaderProgram> Cache::load_asset<graphics::ShaderProgram>(const Path& path) {
        auto shader = load_shader(path);
        m_shaders[path.hash()] = std::weak_ptr(shader);
        return shader;
    }

    template<>
    std::shared_ptr<graphics::Model> Cache::get_resource(const Path& path) {
        auto &model = m_models[path.hash()];
        return get_shared_asset<graphics::Model>(model, path);
    }

    template<>
    std::shared_ptr<graphics::Mesh> Cache::get_resource(const Path& path) {
        auto &mesh = m_meshes[path.hash()];
        return get_shared_asset<graphics::Mesh>(mesh, path);
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
    std::shared_ptr<graphics::ShaderProgram> Cache::get_resource(const Path& path) {
        auto &shader = m_shaders[path.hash()];
        return get_shared_asset<graphics::ShaderProgram>(shader, path);
    }
}
