#include "ec_static_mesh.h"

#include <utility>

#include "../global.h"

namespace entity {
    void EcStaticMeshRenderer::init(std::string filename) {
        this->mesh = { std::move(filename) };
        this->material = global.material;
        this->texture = global.texture;
    }
}
