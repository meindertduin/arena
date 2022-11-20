#pragma once

#include <string>
#include <memory>

#include "texture.h"
#include "mesh.h"
#include "../entity/ec_transform.h"

#include "texture.h"
#include "material.h"

namespace graphics {
    struct TerrainFile {
        std::string heightmap;
        std::string blendmap;
        std::string background_texture;
        std::string r_texture;
        std::string g_texture;
        std::string b_texture;

        glm::vec3 pos;

        float min_height;
        float max_height;
        int width;
        int height;

        std::string material;
    };

    class TerrainTexturePack {
    public:
        explicit TerrainTexturePack(const TerrainFile &file);
        void bind() const;

    private:
        std::shared_ptr<Texture> background_texture;
        std::shared_ptr<Texture> blendmap;
        std::shared_ptr<Texture> r_texture;
        std::shared_ptr<Texture> g_texture;
        std::shared_ptr<Texture> b_texture;
    };

    class Terrain {
    public:
        float max_height = 20;
        float min_height = -20;

        int width;
        int height;

        Terrain(const TerrainFile &file);

        bool get_height(float x, float z, float &y) const;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::shared_ptr<Material>& material() const { return m_material; }
    private:
        friend class TerrainRenderer;

        std::unique_ptr<Mesh> mesh;

        std::shared_ptr<Material> m_material;

        TerrainTexturePack textures;
        entity::ECTransform transform;

        static float barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos);

        std::vector<std::vector<glm::vec3>> positions;
    };
}
