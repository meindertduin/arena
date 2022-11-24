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

    class Terrain : public assets::Resource {
    public:
        float max_height = 20;
        float min_height = -20;

        int width{};
        int height{};

        explicit Terrain(const Path &path) : assets::Resource(path) {}

        bool get_height(float x, float z, float &y) const;

        [[nodiscard]] constexpr ALWAYS_INLINE const std::unique_ptr<Mesh>& mesh() const { return m_mesh; }
        [[nodiscard]] constexpr ALWAYS_INLINE const entity::ECTransform& transform() const { return m_transform; }

        void load(std::size_t size, char *data) override;
        void unload() override { }
    private:
        std::unique_ptr<Mesh> m_mesh;
        entity::ECTransform m_transform;

        static float barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos);

        std::vector<std::vector<glm::vec3>> positions;

        void set_mesh_material(const TerrainFile &file);
    };
}
