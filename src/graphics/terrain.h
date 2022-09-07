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

        Terrain(std::string heightmap_path);
        void render();

        float get_height(float x, float z) const;
    private:
        std::unique_ptr<Sprite16> sprite;
        std::unique_ptr<Mesh> mesh;
        entity::ECTransform transform;

        glm::vec3 **map_points;
    };
}
