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

        bool get_intersect(const glm::vec3 &pos, glm::vec3 &intersect) const;
        bool get_height(float x, float z, float &height) const; 
        bool fast_height(float x, float z, float &height) const;
    private:
        std::unique_ptr<Sprite16> sprite;
        std::unique_ptr<Mesh> mesh;
        entity::ECTransform transform;

        Vertex **vertices;
    };
}
