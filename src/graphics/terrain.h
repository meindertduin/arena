#pragma once

#include <string>
#include <memory>

#include "texture.h"
#include "mesh.h"
#include "../entity/ec_transform.h"

#include "texture.h"

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

        std::string material;
    };

    struct TerrainTexturePack {
    public:
        TerrainTexturePack();
        void bind() const;
    private:
        std::unique_ptr<GpuTexture> background_texture;
        std::unique_ptr<GpuTexture> blendmap;
        std::unique_ptr<GpuTexture> r_texture;
        std::unique_ptr<GpuTexture> g_texture;
        std::unique_ptr<GpuTexture> b_texture;
    };

    struct Terrain {
    public:
        int max_height = 20;
        int min_height = -20;

        int width;
        int height;

        Terrain(const TerrainFile &file);

        bool fast_height(float x, float z, float &y) const;
    private:
        friend class TerrainRenderer;

        std::unique_ptr<Mesh> mesh;

        TerrainTexturePack textures;
        entity::ECTransform transform;

        static float barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos);

        std::vector<std::vector<glm::vec3>> positions;
    };
}
