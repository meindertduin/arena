#pragma once

#include <string>
#include <memory>

#include "texture.h"
#include "mesh.h"
#include "../entity/ec_transform.h"

namespace graphics {
    struct Terrain {
    public:
        static constexpr int MAX_HEIGHT = 40;
        static constexpr int MIN_HEIGHT = -40;

        Terrain(std::string heightmap_path);
        void render();
    private:
        std::unique_ptr<Sprite16> sprite;
        std::unique_ptr<Mesh> mesh;
        entity::ECTransform transform;
    };
}
