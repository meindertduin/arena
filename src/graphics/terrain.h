#pragma once

#include <string>
#include <memory>

#include "texture.h"
#include "mesh.h"
#include "../entity/ec_transform.h"

namespace graphics {
    struct Terrain {
    public:
        static constexpr int MAX_HEIGHT = 20;
        static constexpr int MIN_HEIGHT = -20;

        int width;
        int height;

        Terrain(const std::string& heightmap_path);
        void render();

        bool fast_height(float x, float z, float &y) const;
    private:
        std::unique_ptr<Sprite16> sprite;
        std::unique_ptr<Mesh> mesh;
        entity::ECTransform transform;

        static float barry_centric(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec2 &pos);

        std::vector<std::vector<glm::vec3>> positions;
    };
}
